#define PIN_BOTON 12
#define LED_1 2

// Estados
#define ESPERANDO 0
#define ALERTA 1

int estado = ESPERANDO;
unsigned long tiempoInicioAlerta;
unsigned long tiempoInicioEvento;
int contadorEventos = 0;

void setup() 
{
  pinMode(PIN_BOTON, INPUT_PULLUP);
  pinMode(LED_1, OUTPUT);
}

void loop() 
{
  int val = digitalRead(PIN_BOTON);

  switch (estado) 
  {
    case ESPERANDO:

      if (val == LOW) 
      { 
        // Se invierte la condición para detectar el estado de LOW del botón
        estado = ALERTA;
        tiempoInicioAlerta = millis();
        tiempoInicioEvento = millis();
        contadorEventos = 1;
      }

      break;

    case ALERTA:

      if (millis() - tiempoInicioAlerta > 10000) 
      {
        estado = ESPERANDO;
        contadorEventos = 0;
        digitalWrite(LED_1, LOW);
      } 
      else if (millis() - tiempoInicioEvento > 2000) 
      {
        tiempoInicioEvento = millis(); // Reiniciar tiempoInicioEvento

        if (val == LOW) 
        { // Se invierte la condición para detectar el estado de LOW del botón
          contadorEventos++;
          delay(50); // Se añade un pequeño retardo para evitar rebotes
        }
      }

      if (contadorEventos >= 3) 
      {
        digitalWrite(LED_1, HIGH);
      }

      break;
  }
}
