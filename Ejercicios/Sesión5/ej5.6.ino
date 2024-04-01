// Estados
#define INACTIVO 0
#define DENTRO 1
#define ASCENDENTE 2
#define PARADO 3

// Pines
#define LED_ROJO 4
#define LED_VERDE 3
#define LED_AMARILLO 5
#define PIN_BOTON 2

int state = INACTIVO;
unsigned long tiempoInicio;
int pisoSeleccionado = 0;
int contadorPulsaciones = 0;
unsigned long tiempoUltimaPulsacion = 0;
const unsigned long intervaloPulsacion = 500;

void setup()
{
  pinMode(PIN_BOTON, INPUT_PULLUP);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  int val = digitalRead(PIN_BOTON);
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);

  switch (state)
  {
    case INACTIVO:

      if (val == LOW)
      {
        state = DENTRO;
        tiempoInicio = millis();
        Serial.println("Dentro del ascensor.");
        delay(1000);
        pisoSeleccionado = 0;
        contadorPulsaciones = 0;
        Serial.println("Seleccione un piso (1,2 o 3).");
      }

      break;

    case DENTRO:

      if (val == LOW && millis() - tiempoUltimaPulsacion > intervaloPulsacion)
      {
        contadorPulsaciones++;            // Incrementar el contador de pulsaciones
        tiempoUltimaPulsacion = millis(); // registra el tiempo de la ultima pulsación

        if (contadorPulsaciones <= 3)
        {
          pisoSeleccionado = contadorPulsaciones; // Asignar el número de piso según el contador de pulsaciones
          Serial.print("Piso seleccionado: ");
          Serial.println(pisoSeleccionado);
          state = ASCENDENTE;
          tiempoInicio = millis();
        }
        else
        {
          Serial.println("No se pueden seleccionar más de 3 pisos.");
        }
        delay(500);
      }

      break;

    case ASCENDENTE:

      if (millis() - tiempoInicio >= 1000 * pisoSeleccionado)
      {
        state = PARADO;
        Serial.println("Ha llegado al destino. Pulse el botón para bajar al piso 0.");
      }

      break;

    case PARADO:

      if (val == LOW)
      {
        state = INACTIVO;
        Serial.println("Bajando al piso 0. Ascensor inactivo.");
        delay(1000); // esperar 1 s para evitar el rebote
        pisoSeleccionado = 0;
      }

      break;
  }

  // encender el led correspondiente
  if (state != INACTIVO)
  {
    switch (pisoSeleccionado)
    {
      case 1:
      
        digitalWrite(LED_VERDE, HIGH);
        break;

      case 2:

        digitalWrite(LED_ROJO, HIGH);
        break;

      case 3:

        digitalWrite(LED_AMARILLO, HIGH);
        break;

      default:

        break;
    }
  }
}