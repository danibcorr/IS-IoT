// Estados
#define DESCONECTADO 0
#define CONECTADO 1
#define ACTIVO1 2
#define ACTIVO2 3

// Pines
#define LED_ROJO2 4
#define LED_ROJO3 3
#define LED_ROJO1 5
#define PIN_BOTON 2

// Constantes de tiempo
const unsigned long TIEMPO_PARPADEO = 250;
const unsigned long TIEMPO_PULSACION_CORTA = 3000;
const unsigned long TIEMPO_PULSACION_LARGA = 3000;
const unsigned long TIEMPO_ACTIVO1 = 5000;
const unsigned long TIEMPO_ACTIVO2 = 5000;

// Variables
int estado = DESCONECTADO;
unsigned long tiempoInicioBoton = 0;

void setup() 
{
  pinMode(PIN_BOTON, INPUT_PULLUP);
  pinMode(LED_ROJO1, OUTPUT);
  pinMode(LED_ROJO2, OUTPUT);
  pinMode(LED_ROJO3, OUTPUT);

  Serial.begin(9600);
}

void loop() 
{
  int val = digitalRead(PIN_BOTON);
  unsigned long tiempoActual = millis();

  switch (estado) 
  {
    case DESCONECTADO:

      apagarLEDs();
      Serial.println("Estado: DESCONECTADO. Esperando botón para conectar.");

      if (val == LOW) 
      {
        estado = CONECTADO;
        Serial.println("Conexión establecida. Cambiando al estado CONECTADO.");
      }

      break;

    case CONECTADO:

      parpadearLEDs(TIEMPO_PARPADEO);
      Serial.println("Estado: CONECTADO. Parpadeando LEDs. Esperando pulsación breve o prolongada del botón.");

      if (val == LOW && tiempoActual - tiempoInicioBoton > TIEMPO_PULSACION_LARGA) 
      {
        estado = DESCONECTADO;
        Serial.println("Pulsación prolongada detectada. Volviendo al estado DESCONECTADO.");
      } 
      else if (val == LOW && tiempoActual - tiempoInicioBoton > TIEMPO_PULSACION_CORTA) 
      {
        estado = ACTIVO1;
        Serial.println("Pulsación breve detectada. Cambiando al estado ACTIVO1.");
      } 
      else if (val == HIGH) 
      {
        tiempoInicioBoton = millis(); // Registro del inicio de la pulsación
      }

      break;

    case ACTIVO1:

      parpadearTodosLEDs(TIEMPO_PARPADEO);
      Serial.println("Estado: ACTIVO1. Parpadeo simultáneo de todos los LEDs. Esperando cambio automático o pulsación del botón.");

      if (tiempoActual - tiempoInicioBoton > TIEMPO_ACTIVO1) 
      {
        estado = ACTIVO2;
        Serial.println("Cambio automático al estado ACTIVO2 después de 5000ms.");
      } 
      else if (val == LOW) 
      {
        estado = CONECTADO;
        Serial.println("Pulsación del botón detectada. Cambiando al estado CONECTADO.");
      }
      
      break;

    case ACTIVO2:

      parpadearLEDsDosAUno(TIEMPO_PARPADEO);
      Serial.println("Estado: ACTIVO2. Parpadeo de dos LEDs a uno. Esperando cambio automático o pulsación del botón.");

      if (tiempoActual - tiempoInicioBoton > TIEMPO_ACTIVO2) 
      {
        estado = ACTIVO1;
        Serial.println("Cambio automático al estado ACTIVO1 después de 5000ms.");
      } 
      else if (val == LOW) 
      {
        estado = CONECTADO;
        Serial.println("Pulsación del botón detectada. Cambiando al estado CONECTADO.");
      }

      break;
  }
}

void apagarLEDs() 
{
  digitalWrite(LED_ROJO1, LOW);
  digitalWrite(LED_ROJO2, LOW);
  digitalWrite(LED_ROJO3, LOW);
}

void parpadearLEDs(int tiempoEncendido) 
{
  static unsigned long tiempoAnterior = 0;
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior >= tiempoEncendido) 
  {
    digitalWrite(LED_ROJO1, !digitalRead(LED_ROJO1));
    digitalWrite(LED_ROJO2, !digitalRead(LED_ROJO2));
    digitalWrite(LED_ROJO3, !digitalRead(LED_ROJO3));
    tiempoAnterior = tiempoActual;
  }
}

void parpadearTodosLEDs(int tiempoEncendido) 
{
  static unsigned long tiempoAnterior = 0;
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior >= tiempoEncendido) 
  {
    digitalWrite(LED_ROJO1, HIGH);
    digitalWrite(LED_ROJO2, HIGH);
    digitalWrite(LED_ROJO3, HIGH);

    delay(tiempoEncendido);

    digitalWrite(LED_ROJO1, LOW);
    digitalWrite(LED_ROJO2, LOW);
    digitalWrite(LED_ROJO3, LOW);

    tiempoAnterior = tiempoActual;
  }
}

void parpadearLEDsDosAUno(int tiempoEncendido) 
{
  static unsigned long tiempoAnterior = 0;
  static int contador = 0;
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior >= tiempoEncendido) 
  {
    if (contador % 2 == 0) 
    {
      digitalWrite(LED_ROJO1, HIGH);
      digitalWrite(LED_ROJO2, LOW);
    } 
    else 
    {
      digitalWrite(LED_ROJO1, LOW);
      digitalWrite(LED_ROJO2, HIGH);
    }
    
    digitalWrite(LED_ROJO3, LOW);
    contador++;
    tiempoAnterior = tiempoActual;
  }
}
