//Pines
#define LED_ROJO2 4
#define LED_ROJO3 3
#define LED_ROJO1 5
#define LED_VERDE 7
#define LED_AMARILLO 6
#define PIN_BOTON1 2
#define PIN_BOTON2 8

int velocidad=500;
unsigned long tiempoAnterior = 0;
unsigned long tiempoAnteriorBotones = 0;

void setup() {
  pinMode(LED_ROJO1, OUTPUT);
  pinMode(LED_ROJO2, OUTPUT);
  pinMode(LED_ROJO3, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  Serial.begin(9600);

  pinMode(PIN_BOTON1, INPUT);
  pinMode(PIN_BOTON2, INPUT);
}

void loop() {
  

  // Manejo de botones
    int val1 = digitalRead(PIN_BOTON1);
    int val2=digitalRead(PIN_BOTON2);

    if(val1==HIGH){
      delay(50);
      velocidad-=50; //disminuir la velocidad al presionar el boton1
      if(velocidad<50){
         velocidad=50;
      }
      Serial.print("Velocidad ajustada: ");
      Serial.println(velocidad);
      encenderLEDs(velocidad);
    }

    if(val2==HIGH){
      delay(50);
      velocidad+=50; //aumentar la velocidad al pulsar el boton2
      if(velocidad>1000){
        velocidad=1000; //límite máximo de velocidad
      }
      Serial.print("Velocidad ajustada: ");
      Serial.println(velocidad);
      encenderLEDs(velocidad);

    }
} 

  
void encenderLEDs(int v){ 
  
    // Encender y apagar los LEDs en secuencia
    for (int i = 0; i < 1; i++) {
      // Secuencia de LEDs rojos
      digitalWrite(LED_VERDE, HIGH);
      delay(v);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_ROJO1, HIGH);
      delay(v);
      digitalWrite(LED_ROJO1, LOW);
      digitalWrite(LED_ROJO2, HIGH);
      delay(velocidad);
      digitalWrite(LED_ROJO2, LOW);
      digitalWrite(LED_ROJO3, HIGH);
      delay(v);
      digitalWrite(LED_ROJO3, LOW);
      digitalWrite(LED_AMARILLO, HIGH);
      delay(v);
      digitalWrite(LED_AMARILLO, LOW);
    }

    // Encender y apagar los LEDs en secuencia inversa
    for (int i = 0; i < 1; i++) {
      // Secuencia de LEDs rojos en sentido inverso
      digitalWrite(LED_AMARILLO, HIGH);
      delay(v);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_ROJO3, HIGH);
      delay(v);
      digitalWrite(LED_ROJO3, LOW);
      digitalWrite(LED_ROJO2, HIGH);
      delay(v);
      digitalWrite(LED_ROJO2, LOW);
      digitalWrite(LED_ROJO1, HIGH);
      delay(v);
      digitalWrite(LED_ROJO1, LOW);
      digitalWrite(LED_VERDE, HIGH);
      delay(v);
      digitalWrite(LED_VERDE, LOW);
    }
  
}