#include <Servo.h>

Servo myservo;

int pos;    // variable para almacenar la posición del servo

void setup() 
{
  myservo.attach(9);

  Serial.begin(9600);
  Serial.println("Introduce un ángulo entre 0 y 180 grados:");
}

void loop() 
{
  if (Serial.available()) 
  {
    // lee el ángulo desde el puerto serial
    // Con el SKIP_ALL podemos evitar todos los caracteres diferentes a negativos o numeros
    // y el '\n' permite evitar los saltos de linea que pondrian a 0 el servo
    int angle = Serial.parseInt(SKIP_ALL, '\n');  
    
    if (angle >= 0 && angle <= 180) 
    {
      pos = angle;
      myservo.write(pos);  // mueve el servo a la posición especificada
      Serial.println("El servo se ha movido a la posición: " + String(pos));
    } 
    else 
    {
      Serial.println("Por favor, introduce un número válido entre 0 y 180.");
    }
  }
}