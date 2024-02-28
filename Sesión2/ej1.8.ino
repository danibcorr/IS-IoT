#define LED_ROJO1 8
#define LED_ROJO2 3
#define LED_VERDE 2
#define LED_AMARILLO 5
#define BOTON 6


int estadoBotonAnterior = LOW;
unsigned long tiempoInicioGiro = 0;
unsigned long tiempoGiro = 3000;

void setup() {
  pinMode(LED_ROJO1, OUTPUT);
  pinMode(LED_ROJO2, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(BOTON, INPUT);

}

void loop() {

  int estadoBoton = digitalRead(BOTON);

  if (estadoBoton == HIGH && estadoBotonAnterior == LOW) {
    tiempoInicioGiro = millis();  // Guardar el tiempo de inicio del "giro"
    while (millis() - tiempoInicioGiro < tiempoGiro) {
      // "Girar" los LEDS
      digitalWrite(LED_ROJO1, HIGH);
      delay(300);
      digitalWrite(LED_ROJO1, LOW);
      digitalWrite(LED_AMARILLO, HIGH);
      delay(300);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_ROJO2, HIGH);
      delay(300);
      digitalWrite(LED_ROJO2, LOW);
      digitalWrite(LED_VERDE, HIGH);
      delay(300);
      digitalWrite(LED_VERDE, LOW);


    }

    // Establecer un valor (por ejemplo, encender los LED)
    digitalWrite(LED_ROJO1, HIGH);
    digitalWrite(LED_AMARILLO, HIGH);
    digitalWrite(LED_ROJO2, HIGH);
    digitalWrite(LED_VERDE, HIGH);
    //delay(400);

  }

  estadoBotonAnterior = estadoBoton;



}

