#include <SoftwareSerial.h>

#define RX_PIN 10  // Pin conectado al pin TX del HC-06
#define TX_PIN 18  // Pin conectado al pin RX del HC-06

SoftwareSerial bluetoothSerial(RX_PIN, TX_PIN);

void setup() 
{
    // Inicialización del puerto serie para la comunicación serial
    Serial.begin(9600);
    
    // Inicialización de la comunicación serial con el módulo HC-06
    bluetoothSerial.begin(115200);
}

void loop() 
{
    // Verifica si hay datos disponibles para leer desde el módulo Bluetooth
    if (bluetoothSerial.available()) 
    {
        // Lee los datos recibidos desde el módulo Bluetooth
        char receivedChar = bluetoothSerial.read();
        
        // Imprime los datos recibidos por el puerto serie
        Serial.print(receivedChar);
    }
}
