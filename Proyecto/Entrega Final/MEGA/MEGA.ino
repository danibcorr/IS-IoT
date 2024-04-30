String data;
float humedad, temperatura, luminosidad;

void setup() 
{
    // Inicia la comunicación serial a 9600 baudios
    Serial.begin(9600);  

    // Inicia la comunicación serial en el puerto 1 a 115200 baudios
    // Igual a la configuración Bluetooth de la ESP32
    Serial1.begin(115200);  
}

void loop() 
{
    if (Serial1.available()) 
    {
        // Lee la cadena de datos hasta que se encuentre un salto de línea
        data = Serial1.readStringUntil('\n'); 

        // Elimina los espacios en blanco al principio y al final de la cadena
        data.trim();

        // Si la línea es "Comunicacion cortada", terminar la adquisición de datos
        if (data == "Comunicacion cortada") 
        {
            Serial.println("Comunicacion cortada");
            Serial1.write('ON');

            return;
        }
        else if (data == "Comunicacion activada")
        {
            // De esta forma no se mostraran por el puerto serie valores 0
            // de la adquisición de los datos, le estamos dando un margen
            Serial1.write('OFF');
            return;
        }

        // Encuentra la posición de la primera coma
        int firstCommaIndex = data.indexOf(',');  

        // Encuentra la posición de la segunda coma
        int secondCommaIndex = data.indexOf(',', firstCommaIndex + 1);  

        // Divide la cadena de datos en partes y las convierte a float
        humedad = data.substring(0, firstCommaIndex).toFloat();
        temperatura = data.substring(firstCommaIndex + 1, secondCommaIndex).toFloat();
        luminosidad = data.substring(secondCommaIndex + 1).toFloat();

        // Imprime los valores de los sensores en la misma línea
        Serial.print("Humedad: ");
        Serial.print(humedad);
        Serial.print("%, Temperatura: ");
        Serial.print(temperatura);
        Serial.print("°C, Luminosidad: ");
        Serial.println(luminosidad);
    }
}

