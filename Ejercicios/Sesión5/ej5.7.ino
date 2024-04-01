// Estados
#define DESCONECTADA 0
#define CONECTADA 1
#define ACTIVA_1 2
#define ACTIVA_2 3

// Pines
#define LED_1 4
#define LED_2 3
#define LED_3 5
#define PIN_BOTON 2

// Constantes de tiempo
const unsigned long TIEMPO_PULSACION_CORTA = 3000;
const unsigned long TIEMPO_PULSACION_LARGA = 3000;
const unsigned long TIEMPO_ACTIVA = 5000;

int estado = DESCONECTADA;
unsigned long tiempoInicio = 0;

void setup() 
{
  pinMode(PIN_BOTON, INPUT_PULLUP);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  Serial.begin(9600);
}

void loop() 
{
  int val = digitalRead(PIN_BOTON);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);

  switch (estado) 
  {
    case DESCONECTADA:

      if (val == LOW) 
      {
        estado = CONECTADA;
        tiempoInicio = millis();
        Serial.println("Estado: Conectada");
      }

      break;

    case CONECTADA:

      if (val == LOW) 
      {
        unsigned long tiempoPulsacion = millis() - tiempoInicio;

        if (tiempoPulsacion < TIEMPO_PULSACION_CORTA) 
        {
          estado = ACTIVA_1;
          tiempoInicio = millis();
          Serial.println("Estado: Activa-1");
        } 
        else if (tiempoPulsacion > TIEMPO_PULSACION_LARGA) 
        {
          estado = DESCONECTADA;
          Serial.println("Estado: Desconectada");
        }
      } 
      else 
      {
        digitalWrite(LED_1, HIGH);
      }

      break;

    case ACTIVA_1:

      if (val == LOW) 
      {
        estado = CONECTADA;
        tiempoInicio = millis();
        Serial.println("Estado: Conectada");
      } 
      else if (millis() - tiempoInicio >= TIEMPO_ACTIVA) 
      {
        estado = ACTIVA_2;
        tiempoInicio = millis();
        Serial.println("Estado: Activa-2");
      } 
      else 
      {
        digitalWrite(LED_2, HIGH);
      }

      break;

    case ACTIVA_2:

      if (val == LOW) 
      {
        estado = CONECTADA;
        tiempoInicio = millis();
        Serial.println("Estado: Conectada");
      } 
      else if (millis() - tiempoInicio >= TIEMPO_ACTIVA) 
      {
        estado = ACTIVA_1;
        tiempoInicio = millis();
        Serial.println("Estado: Activa-1");
      } 
      else 
      {
        digitalWrite(LED_3, HIGH);
      }
      
      break;
  }
}
