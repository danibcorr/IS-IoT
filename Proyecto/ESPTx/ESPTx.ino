#include <BluetoothSerial.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

// Comprobación de si Bluetooth está habilitado en la configuración
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
    #error Bluetooth is not enabled! Please run `make menuconfig` to enable it
#endif

// Comprobación de si el perfil SPP de Bluetooth está habilitado
#if !defined(CONFIG_BT_SPP_ENABLED)
    #error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

// Inicialización de la instancia de BluetoothSerial
BluetoothSerial SerialBT;

// Definir el nombre del dispositivo Bluetooth al que te quieres conectar
String slaveName = "HC06_MEGARx";
String masterName = "ESP32Tx";

#include <DHT.h>

// Definición de pines
#define DHTPIN 16
#define DHTTYPE DHT11
#define BUTTON_PIN 17
#define LED_RED 4
#define LED_GREEN 2

// Inicialización del sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Variable para controlar la transmisión de datos
volatile bool transmitData = true;

// Configuracion para antirrebote via Software en combinacion con Pull-Up interno
unsigned long ultimoTiempoPulsado = 0;  // La última vez que el botón fue pulsado
unsigned long tiempoDebounce = 200;     // Tiempo de debounce en milisegundos

// Función de interrupción para el botón
void IRAM_ATTR handleButtonInterrupt()
{
    if ((millis() - ultimoTiempoPulsado) > tiempoDebounce) 
    {
        transmitData = !transmitData; // Invierte el estado de la transmisión de datos
        digitalWrite(LED_RED, !transmitData); // Apaga o enciende el LED rojo dependiendo del estado de la transmisión
        digitalWrite(LED_GREEN, LOW); // Apaga el LED verde

        if (transmitData == true)
        {
            SerialBT.println("Comunicacion activada");
            Serial.println("Comunicacion activada");
        }
        else
        {
            SerialBT.println("Comunicacion cortada");
            Serial.println("Comunicacion cortada");
        }

        ultimoTiempoPulsado = millis();
    }
}

void setup()
{
    // Inicialización del puerto serie para la comunicación serial
    Serial.begin(115200);

    // Inicialización del dispositivo Bluetooth con el nombre "ESP32test"
    SerialBT.begin(masterName, true);
    Serial.printf("The device \"%s\" started in master mode, make sure slave BT device is on!\n", masterName.c_str());

    // Configuracion Bluetooth esclavo HC-06
    SerialBT.setPin("1111"); // Pin acceso HC-06
    Serial.println("Using PIN");
    bool connected = SerialBT.connect(slaveName);
    Serial.printf("Connecting to slave BT device named \"%s\"\n", slaveName.c_str());

    if(connected) 
    {
      Serial.println("Connected Successfully to slave!");
    } 
    else 
    {
      while(!SerialBT.connected(10000)) 
      {
        Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
      }
    }

    // Configuración de pines
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Configura el pin del botón como entrada con resistencia de pull-up
    pinMode(LED_RED, OUTPUT); // Configura el pin del LED rojo como salida
    pinMode(LED_GREEN, OUTPUT); // Configura el pin del LED verde como salida

    // Asocia la función de interrupción al pin del botón
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonInterrupt, FALLING);

    // Inicialización del sensor DHT
    dht.begin();
}

void loop()
{
    // Bucle principal

    if (transmitData)
    {
        // Si se va a transmitir datos

        // Lee la humedad y la temperatura del sensor DHT
        float humidity = dht.readHumidity();
        float temperature = dht.readTemperature();

        // Imprime los datos por el monitor serie
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.print("% Temperature: ");
        Serial.print(temperature);
        Serial.println("°C");

        // Transmite los datos por Bluetooth
        SerialBT.println("Humedad: " + String(humidity) + "% Temperatura: " + String(temperature) + "°C");

        // Alterna el estado del LED verde
        digitalWrite(LED_GREEN, !digitalRead(LED_GREEN));
    }

    delay(5000); // Espera 5 segundos
}