//Estados
#define DESCONECTADO 0
#define CONECTADO 1
#define ACTIVO1 2
#define ACTIVO2 3


//Pines
#define LED_ROJO2 4
#define LED_ROJO3 3
#define LED_ROJO1 5
#define PIN_BOTON 2

int estado = DESCONECTADO;
unsigned long tiempoInicioBoton=0;


void setup() {
  pinMode(PIN_BOTON, INPUT_PULLUP);
  pinMode(LED_ROJO1, OUTPUT);
  pinMode(LED_ROJO2, OUTPUT);
  pinMode(LED_ROJO3, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  int val = digitalRead(PIN_BOTON);
  
  switch(estado){
    case DESCONECTADO:
      apagarLEDs();
      Serial.println("Estado: DESCONECTADO. Esperando botón para conectar.");
      if(val==LOW){
        estado=CONECTADO;
        Serial.println("Conexión establecida. Cambiando al estado CONECTADO.");
      }
      break;

    case CONECTADO:
    parpadearLEDs(250);
    Serial.println("Estado: CONECTADO. Parpadeando LEDs. Esperando pulsación breve o prolongada del botón.");
    if (val == LOW) {
    tiempoInicioBoton = millis(); // Registrar el inicio de la pulsación
    while (digitalRead(PIN_BOTON) == LOW) {} // Esperar a que se suelte el botón
    unsigned long tiempoPulsacion = millis() - tiempoInicioBoton; // Calcular la duración de la pulsación
    if (tiempoPulsacion < 3000) {
      estado = ACTIVO1;
      Serial.println("Pulsación breve detectada. Cambiando al estado ACTIVO1.");
    } else {
        estado = DESCONECTADO;
        Serial.println("Pulsación prolongada detectada. Volviendo al estado DESCONECTADO.");
    }
  }
   
    break;

  case ACTIVO1:
    parpadearTodosLEDs(500);
    Serial.println("Estado: ACTIVO1. Parpadeo simultáneo de todos los LEDs. Esperando cambio automático o pulsación del botón.");
      if (millis() - tiempoInicioBoton > 5000) {
        estado = ACTIVO2;
        Serial.println("Cambio automático al estado ACTIVO2 después de 5000ms.");
      }
      if (val == LOW) {
        estado = CONECTADO;
        Serial.println("Pulsación del botón detectada. Cambiando al estado CONECTADO.");
      }
    break;

  case ACTIVO2:
    parpadearLEDsDosAUno(250);
    Serial.println("Estado: ACTIVO2. Parpadeo de dos LEDs a uno. Esperando cambio automático o pulsación del botón.");
      if (millis() - tiempoInicioBoton > 5000) {
        estado = ACTIVO1;
        Serial.println("Cambio automático al estado ACTIVO1 después de 5000ms.");
      }
      if (val == LOW) {
        estado = CONECTADO;
        Serial.println("Pulsación del botón detectada. Cambiando al estado CONECTADO.");
      }
    break;  

  }
}  

void apagarLEDs() {
  digitalWrite(LED_ROJO1, LOW);
  digitalWrite(LED_ROJO2, LOW);
  digitalWrite(LED_ROJO3, LOW);
}

void parpadearLEDs(int tiempoEncendido) {
  static unsigned long tiempoAnterior = 0;
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior >= tiempoEncendido) {
    digitalWrite(LED_ROJO1, !digitalRead(LED_ROJO1));
    digitalWrite(LED_ROJO2, !digitalRead(LED_ROJO2));
    digitalWrite(LED_ROJO3, !digitalRead(LED_ROJO3));
    tiempoAnterior = tiempoActual;
  }
}

void parpadearTodosLEDs(int tiempoEncendido) {
  static unsigned long tiempoAnterior = 0;
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior >= tiempoEncendido) {
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

void parpadearLEDsDosAUno(int tiempoEncendido) {
  static unsigned long tiempoAnterior = 0;
  static int contador = 0;
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior >= tiempoEncendido) {
    if (contador % 2 == 0) {
      digitalWrite(LED_ROJO1, HIGH);
      digitalWrite(LED_ROJO2, LOW);
    } else {
      digitalWrite(LED_ROJO1, LOW);
      digitalWrite(LED_ROJO2, HIGH);
    }
    digitalWrite(LED_ROJO3, LOW);
    contador++;
    tiempoAnterior = tiempoActual;
  }
}
