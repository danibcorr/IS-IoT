#define NUM_LEDS 8
#define PIN_BOTON_AUMENTAR 12
#define PIN_BOTON_DISMINUIR 13

int ledPins[NUM_LEDS] = {2, 3, 4, 5, 6, 7, 8, 9}; // Pines de los LEDs
int velocidad = 200; // Velocidad inicial en milisegundos

void setup() 
{
  for (int i = 0; i < NUM_LEDS; i++) 
  {
    pinMode(ledPins[i], OUTPUT);
  }
  
  pinMode(PIN_BOTON_AUMENTAR, INPUT);
  pinMode(PIN_BOTON_DISMINUIR, INPUT);
}

void loop() 
{
  // Comprobar si se ha pulsado el botón para aumentar la velocidad
  if (digitalRead(PIN_BOTON_AUMENTAR) == HIGH) 
  {
    velocidad -= 50;

    if (velocidad < 50) 
    {
      velocidad = 50;
    }

    delay(200); // Debounce
  }

  // Comprobar si se ha pulsado el botón para disminuir la velocidad
  if (digitalRead(PIN_BOTON_DISMINUIR) == HIGH) 
  {
    velocidad += 50;

    if (velocidad > 1000) 
    {
      velocidad = 1000;
    }

    delay(200); // Debounce
  }

  // Secuencia de encendido de izquierda a derecha
  for (int i = 0; i < NUM_LEDS; i++) 
  {
    digitalWrite(ledPins[i], HIGH);
    delay(velocidad);
    digitalWrite(ledPins[i], LOW);
  }

  // Secuencia de encendido de derecha a izquierda
  for (int i = NUM_LEDS - 1; i >= 0; i--) 
  {
    digitalWrite(ledPins[i], HIGH);
    delay(velocidad);
    digitalWrite(ledPins[i], LOW);
  }
}
