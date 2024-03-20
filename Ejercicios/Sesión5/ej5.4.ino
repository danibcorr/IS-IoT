//Estados
#define APAGADO 0
#define ENCENDIDO 1

//Pines
#define LED_ROJO 3
#define LED_VERDE 4
#define PIN_BOTON 2

int state = APAGADO;
bool ledVerdeEncendido = false;

void setup() {
  pinMode(PIN_BOTON, INPUT_PULLUP);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  
}

void loop() {

  int val = digitalRead(PIN_BOTON);
  switch(state){
    case APAGADO:
      digitalWrite(LED_ROJO, LOW);
      if(val == LOW){
      digitalWrite(LED_ROJO, HIGH);
      state = ENCENDIDO;
      }
      break;
  case ENCENDIDO:
    digitalWrite(LED_VERDE, ledVerdeEncendido ? HIGH : LOW); // Enciende o apaga el LED verde basado en el estado actual
      if (val == LOW) {
        ledVerdeEncendido = !ledVerdeEncendido; // Cambia el estado del LED verde
        delay(100); 
      }
      else {
        digitalWrite(LED_VERDE, LOW); // Apaga el LED verde si el botón no está presionado
        state = APAGADO;
      }
    break;
  }
}