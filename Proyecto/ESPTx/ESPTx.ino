// Librerias
#include <BluetoothSerial.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <DHT.h>

// Definición de pines
#define DHTTYPE DHT11
#define LDRPIN 32
#define DHTPIN 33
#define BUTTON_PIN 23
#define BUZZERPIN 14
#define LED_RED 5
#define LED_YELLOW 21

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

// Inicialización del sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Variable para controlar la transmisión de datos
volatile bool transmitData = true;

// Configuracion para antirrebote via Software en combinacion con Pull-Up interno
// La última vez que el botón fue pulsado
unsigned long ultimoTiempoPulsado = 0;

// Tiempo de debounce en milisegundos  
unsigned long tiempoDebounce = 200; 

// Variables para la gestión de reintentos
const int RETRY_INTERVAL = 2000;
bool isConnected = false;
const int num_intentos = 3;

bool connectToSlave(const String &slaveName) 
{
    // Intenta conectar al dispositivo esclavo
    bool connected = SerialBT.connect(slaveName);
    Serial.printf("Conectando al dispositivo esclavo Bluetooth llamado \"%s\"\n", slaveName.c_str());
    
    int retryCount = 0;

    // Verifica si la conexión se realizó correctamente
    while (!connected && retryCount < num_intentos) 
    {
        // Si la conexión falla, imprime un mensaje de error
        Serial.println("Error al conectar. Asegúrese de que el dispositivo remoto esté disponible y dentro del alcance.");

        // Espera antes de volver a intentar la conexión
        delay(RETRY_INTERVAL);

        // Intenta conectar de nuevo
        connected = SerialBT.connect(slaveName);

        // Aumentamos el numero de intentos
        retryCount++;
    }

    if (connected) 
    {
        Serial.println("¡Conectado exitosamente al esclavo!");
    }
    else
    {
        Serial.println("No se pudo conectar al esclavo...");
    }

    return connected;
}

// Función de interrupción para el botón
void IRAM_ATTR handleButtonInterrupt()
{
    if ((millis() - ultimoTiempoPulsado) > tiempoDebounce) 
    {
        // Invierte el estado de la transmisión de datos
        transmitData = !transmitData;       

        // Apaga o enciende el LED rojo dependiendo del estado de la transmisión    
        digitalWrite(LED_RED, !transmitData);  

        // Apaga el LED amarillo 
        digitalWrite(LED_YELLOW, LOW);           

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
    Serial.begin(9600);

    // Inicialización del dispositivo Bluetooth con el nombre "ESP32test"
    SerialBT.begin(masterName, true);
    Serial.printf("El dispositivo \"%s\" arrancó en modo maestro, ¡asegúrese de que el dispositivo BT esclavo está encendido!\n", masterName.c_str());

    // Configuracion Bluetooth esclavo HC-06
    SerialBT.setPin("1111");            // Pin acceso HC-06
    Serial.println("Utilizando PIN");

    // Intenta conectar al dispositivo esclavo
    if (!connectToSlave(slaveName)) 
    {
        Serial.println("No se pudo conectar al esclavo...");
    }

    // Configura el pin del botón como entrada con resistencia de pull-up   
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Configura el pin del LED rojo como salida  
    pinMode(LED_RED, OUTPUT);

    // Configura el pin del LED amarillo como salida           
    pinMode(LED_YELLOW, OUTPUT);

    // Configura el pin del buzzer               
    pinMode(BUZZERPIN, OUTPUT);

    // Configura el pin del LDR         
    pinMode(LDRPIN, INPUT);             

    // Asocia la función de interrupción al pin del botón
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonInterrupt, FALLING);

    // Inicialización del sensor DHT
    dht.begin();
}

void loop()
{
    // Intenta reconectar si la conexión se perdió
    if (!SerialBT.connected()) 
    {
        Serial.println("¡La conexión con el dispositivo esclavo se perdió! Intentando reconectar...");

        digitalWrite(LED_YELLOW, LOW);
        digitalWrite(LED_RED, HIGH);  

        if (!connectToSlave(slaveName)) 
        {
            Serial.println("No se pudo reconectar al esclavo...");

            // Espera un tiempo antes de intentar reconectar nuevamente
            delay(RETRY_INTERVAL); 

            // Sal del loop para evitar el resto del código
            return; 
        }
    }

    // Si la conexión está activa, procede con la transmisión de datos
    if (transmitData)
    {
        digitalWrite(LED_RED, LOW);

        // Leer la humedad y la temperatura del sensor DHT
        float humedad = dht.readHumidity();
        float temperatura = dht.readTemperature();

        // Leer el valor de la LDR
        float luminosidad = analogRead(LDRPIN);

        if (!isnan(humedad) && !isnan(temperatura) && !isnan(luminosidad)) 
        {
            // Imprime los datos por el monitor serie
            Serial.print("Humedad: ");
            Serial.print(humedad);
            Serial.print("%, Temperatura: ");
            Serial.print(temperatura);
            Serial.print("°C, Luminosidad: ");
            Serial.println(luminosidad);

            // Transmite los datos por Bluetooth
            SerialBT.print(humedad);
            SerialBT.print(",");
            SerialBT.print(temperatura);
            SerialBT.print(",");
            SerialBT.println(luminosidad);

            // Alterna el estado del LED amarillo
            digitalWrite(LED_YELLOW, !digitalRead(LED_YELLOW));
        }
        else
        {
            Serial.println("Error al leer los sensores.");
        }
    }

    // Espera 5 segundos
    delay(5000); 
}