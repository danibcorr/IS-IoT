#define LED_ROJO1 8
#define LED_ROJO2 3
#define LED_VERDE 2
#define LED_AMARILLO 5
#define BOTON 6

int estadoBotonAnterior = LOW;
unsigned long tiempoInicioGiro = 0;
unsigned long tiempoGiro = 3000;

void escribirLed(int ledPin, int estado)
{
  digitalWrite(ledPin, estado);
  delay(250);
}

void setup() 
{
  pinMode(LED_ROJO1, OUTPUT);
  pinMode(LED_ROJO2, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(BOTON, INPUT_PULLUP);

  // Inicializar el generador de números aleatorios
  randomSeed(analogRead(0));
}

void loop() 
{
  int estadoBoton = digitalRead(BOTON);

  if (estadoBoton == LOW) 
  {
    tiempoInicioGiro = millis();  // Guardar el tiempo de inicio del "giro"
    
    while (millis() - tiempoInicioGiro < tiempoGiro) 
    {
      escribirLed(LED_ROJO1, random(2));
      escribirLed(LED_ROJO2, random(2));
      escribirLed(LED_VERDE, random(2));
      escribirLed(LED_AMARILLO, random(2));
    }
  }
}
