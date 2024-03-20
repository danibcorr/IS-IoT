//Estados
#define INACTIVO 0
#define DENTRO 1
#define ASCENDENTE 2
#define PARADO 3


//Pines
#define LED_ROJO 4
#define LED_VERDE 3
#define LED_AMARILLO 5
#define PIN_BOTON 2

int state = INACTIVO;
unsigned long tiempoInicio;
int pisoSeleccionado = 0;

void setup() {
  pinMode(PIN_BOTON, INPUT_PULLUP);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {

  int val = digitalRead(PIN_BOTON);
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);

  switch(state){
    case INACTIVO:
      if (val==LOW){
        state=DENTRO;
        tiempoInicio=millis();
        Serial.println("Dentro del ascensor. Seleccione un piso (1,2 o 3).");
      }
      break;
  case DENTRO:
    if (millis() - tiempoInicio >= 5000) {
        state = INACTIVO;
        Serial.println("No se ha seleccionado ningún piso. Volviendo al estado inactivo.");
      }
      else if (val == LOW) {
        pisoSeleccionado = (pisoSeleccionado % 3) + 1; // Ciclar entre pisos 1, 2 y 3
        Serial.print("Piso seleccionado: ");
        Serial.println(pisoSeleccionado);
        state = ASCENDENTE;
        tiempoInicio = millis();
      }

      break;

  case ASCENDENTE:
    if (millis() - tiempoInicio >= 1000) {
        if (pisoSeleccionado < 3) {
          Serial.println("Ascendiendo al siguiente piso...");
          pisoSeleccionado++;
          tiempoInicio = millis();
        }
        else {
          state = PARADO;
          Serial.println("Ha llegado al destino. Pulse el botón para bajar al piso 0.");
        }
      }

    break;
  case PARADO:
    if(val==LOW){
      state=INACTIVO;
      Serial.println("Bajando al piso 0. Ascensor inactivo.");
      pisoSeleccionado = 0;
      delay(1000); //esperar 1 s para evitar el rebote del
    }

    break;  
  }

  //encender el led correspondiente
  if (state != INACTIVO) {
    switch (pisoSeleccionado) {
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