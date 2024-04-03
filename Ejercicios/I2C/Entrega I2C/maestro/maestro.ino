// Codigo maestro
#include <Wire.h>

// Definimos los pines para el botón y el LED
#define PIN_BOTON 2
#define PIN_LED 4

// Configuracion para antirrebote via Software en combinacion con Pull-Up interno
unsigned long ultimoTiempoPulsado = 0;  // La última vez que el botón fue pulsado
unsigned long tiempoDebounce = 200;     // Tiempo de debounce en milisegundos

void setup() 
{
  // Configuramos el pin del botón como entrada y el del LED como salida
  pinMode(PIN_BOTON, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  
  // Iniciamos el bus I2C como maestro
  Wire.begin(); 

  Serial.begin(9600);
}

void loop() 
{
  // Leemos el estado del botón
  int estadoBoton = digitalRead(PIN_BOTON);
  
  // Si el botón está presionado
  if (((millis() - ultimoTiempoPulsado) > tiempoDebounce) && (estadoBoton == LOW))
  { 
    Serial.println("Boton maestro pulsado.");
    // Transmitimos al dispositivo #8
    Wire.beginTransmission(8); 
    // Enviamos un byte
    Wire.write(1);           
    // Detenemos la transmisión
    Wire.endTransmission();   
    ultimoTiempoPulsado = millis(); 
  }

  // Solicita 1 byte al dispositivo esclavo #8
  Wire.requestFrom(8, 1); 

  while (Wire.available() && Wire.read() == 1) 
  {
    Serial.println("Maestro recibe pulsacion esclavo.");
    digitalWrite(PIN_LED, digitalRead(PIN_LED) == HIGH ? LOW : HIGH);
  }
}
