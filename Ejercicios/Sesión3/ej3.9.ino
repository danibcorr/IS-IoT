#include <DHT.h>

// Cambiar segun el pin digital al que este conectado el sensor y
// el modelo del propio sensor
DHT dht(6, DHT22);

#define ledAmarillo 2 // Pin digital para el LED amarillo
#define ledVerde 3 // Pin digital para el LED verde
#define ledRojo 4 // Pin digital para el LED rojo

void encenderLed(int pin) 
{
  digitalWrite(ledAmarillo, LOW); // Apagar LED amarillo
  digitalWrite(ledVerde, LOW); // Apagar LED verde
  digitalWrite(ledRojo, LOW); // Apagar LED rojo
  digitalWrite(pin, HIGH); // Encender LED correspondiente al pin proporcionado
}

void setup() 
{
  // Configuracion de los leds
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  // Configuracion para visualizacion del puerto serie
  Serial.begin(9600);

  dht.begin();
}

void loop() 
{
  // Leer temperatura del sensor
  float temperatura = dht.readTemperature();

  Serial.print(F("%  Temperatura: "));
  Serial.print(temperatura);
  Serial.println(F("°C "));

  if (temperatura < 0) 
  {
    encenderLed(ledAmarillo); // Encender LED amarillo si la temperatura está por debajo de 0°C
  }
  else if (temperatura > 40) 
  {
    encenderLed(ledRojo); // Encender LED rojo si la temperatura está por encima de 40°C
  } 
  else 
  {
    encenderLed(ledVerde); // Encender LED verde si la temperatura está entre 0°C y 40°C
  }
  
  delay(1000); // Esperar 1 segundo antes de tomar otra muestra
}