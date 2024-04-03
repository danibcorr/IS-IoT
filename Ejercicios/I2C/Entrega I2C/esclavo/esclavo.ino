// Codigo esclavo
#include <Wire.h>

// Definimos los pines para el botón y el LED
#define PIN_BOTON 2
#define PIN_LED 1

// Configuracion para antirrebote via Software en combinacion con Pull-Up interno
unsigned long ultimoTiempoPulsado = 0;  // La última vez que el botón fue pulsado
unsigned long tiempoDebounce = 200;     // Tiempo de debounce en milisegundos

void setup() 
{
  // Configuramos el pin del botón como entrada y el del LED como salida
  pinMode(PIN_BOTON, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  // Iniciamos el bus I2C con la dirección #8
  Wire.begin(8);                
  
  // Registramos el evento de recepción
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  Serial.begin(9600);
}

void loop() 
{

}

// Función que se ejecuta cada vez que se reciben datos del maestro
void receiveEvent(int howMany) 
{
  while (Wire.available()) 
  {
    // Recibir byte como carácter
    int c = Wire.read(); 

    if (c == 1) 
    {
      Serial.println("Esclavo recibe pulsacion maestro.");
      digitalWrite(PIN_LED, digitalRead(PIN_LED) == HIGH ? LOW : HIGH);
    } 
  }
}

// Función que se ejecuta cada vez que el maestro solicita datos
void requestEvent() 
{
  int estadoBoton = digitalRead(PIN_BOTON);

  if (((millis() - ultimoTiempoPulsado) > tiempoDebounce) && (estadoBoton == LOW)) 
  {
    Wire.write(1);
    Serial.println("Boton esclavo pulsado.");
    ultimoTiempoPulsado = millis();
  }
}