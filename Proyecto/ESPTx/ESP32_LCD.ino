//Libreria para el display
#include <LiquidCrystal_I2C.h>
#include "DHTesp.h"

//Declaramos nuestro objeto, direccion I2C, numero Columnas, filas.
LiquidCrystal_I2C lcd(0x27, 16, 2);

DHTesp sensor;
int dhtPin=13;
const int buzzerPin = 14; // Pin del buzzer

void setup() 
{
  Serial.begin(115200);
  //Iniciamos la pantalla
  lcd.init();
  lcd.backlight();

  //ubicamos cursor
  lcd.setCursor(0,0);
  lcd.print("Hola");
  delay(1000);
  lcd.clear();
  delay(1000);
  lcd.print("GDS0543");

  pinMode(dhtPin, INPUT);
  //configurar sensor
  sensor.setup(dhtPin, DHTesp::DHT22);
  pinMode(buzzerPin, OUTPUT); // Configurar el buzzer como salida
}

void loop() 
{
  //leer los datos detemperatura y humedad 
  TempAndHumidity lectura= sensor.getTempAndHumidity();
  //despegarlos en pantalla
  //si la temperatura es mayor a 50 limpia pantalla y pon una alerta
  if(lectura.temperature>50)
  {
    lcd.setCursor(0,0);
    lcd.print("Peligro");
    lcd.setCursor(0,1);
    lcd.print("Temp Alta: "+String(lectura.temperature, 1)+"C");
    // Activar el buzzer
    tone(buzzerPin, 2000); // Frecuencia del sonido
  }
  else
  {//si no coloca la temperatura y humedad nuevamente
    lcd.setCursor(0,0);
    lcd.print("Temperatura:"+String(lectura.temperature, 2)+"C");
    lcd.setCursor(0,1);
    lcd.print("Humedad:"+String(lectura.humidity, 2)+"%");
    // Desactivar el buzzer
    noTone(buzzerPin);
  }
  //Espera de 2 segundos para nueva lectura
  delay(2000);
  lcd.clear();
}