const int ledRojo = 3;
const int ledVerde = 4;
const int boton = 2;

byte estadoVerde = LOW;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(boton, INPUT_PULLUP);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  int estadoBoton = digitalRead(boton);
  unsigned long ms = millis();
  
  if (estadoBoton == LOW)
  {
    digitalWrite(ledRojo, 1);
    if (estadoVerde == LOW)
    {
      digitalWrite(ledVerde, 1);
      estadoVerde = HIGH;
    }
    else
    {
      digitalWrite(ledVerde, 0);
      estadoVerde = LOW;
    }
  }
  else
  {
    digitalWrite(ledRojo, 0);
  }
}
