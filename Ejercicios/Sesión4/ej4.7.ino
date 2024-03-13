#include <Servo.h>

Servo myservo; 

const int pinBoton = 2;
volatile int velocidad = 0;
int pos = 0;
const int numEstados = 4; // Hay 4 estados, 3 de velocidad y uno quieto

// Configuracion para antirrebote via Software en combinacion con Pull-Up interno
unsigned long ultimoTiempoPulsado = 0;  // La última vez que el botón fue pulsado
unsigned long tiempoDebounce = 200;     // Tiempo de debounce en milisegundos

void setup() 
{
    myservo.attach(9);  
    pinMode(pinBoton, INPUT_PULLUP);

    // Utilizar interrupciones para la gestion instantanea del boton
    attachInterrupt(digitalPinToInterrupt(pinBoton), cambiarVelocidad, CHANGE);

    Serial.begin(9600);
}

void loop() 
{
    switch (velocidad) 
    {
        case 0:

            // Servo para
            break;

        case 1:

            // Velocidad 1
            for (pos = 0; pos <= 180; pos += 1) 
            {
                myservo.write(pos);
                delay(15);
            }

            for (pos = 180; pos >= 0; pos -= 1) 
            {
                myservo.write(pos);
                delay(15);
            }

            break;

        case 2:

            // Velocidad 2
            for (pos = 0; pos <= 180; pos += 2) 
            {
                myservo.write(pos);
                delay(15);
            }

            for (pos = 180; pos >= 0; pos -= 2) 
            {
                myservo.write(pos);
                delay(15);
            }

            break;

        case 3:

            // Velocidad 3
            for (pos = 0; pos <= 180; pos += 3) 
            {
                myservo.write(pos);
                delay(15);
            }

            for (pos = 180; pos >= 0; pos -= 3)
            {
                myservo.write(pos);
                delay(15);
            }

            break;
    }
}

void cambiarVelocidad() 
{
    if ((millis() - ultimoTiempoPulsado) > tiempoDebounce) 
    {
        velocidad = (velocidad + 1) % numEstados;
        Serial.println("Boton pulsado");
        ultimoTiempoPulsado = millis();
    }
}