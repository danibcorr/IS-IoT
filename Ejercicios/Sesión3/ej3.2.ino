const int ledVerde = 4;
const int ledRojo = 3;

const int periodoVerde = 800; // ms
const int periodoRojo = 5000; // ms

byte estadoVerde = LOW;

int nivel = 0;
const int incPWD = 5;
unsigned long last_ms_digital = 0;
unsigned long last_ms_PWD = 0;

void setup() 
{
  pinMode(ledVerde, OUTPUT);
}

void loop() 
{
  unsigned long curr_ms = millis();
  
  if (curr_ms - last_ms_digital >= (periodoVerde / 2))
  {
    last_ms_digital = curr_ms;
    estadoVerde = (estadoVerde == LOW ? HIGH : LOW);
    digitalWrite(ledVerde, estadoVerde); 
  }
  
  // La división entre 20 altera la velocidad a la que el led alcanza el ciclo de trabajo
  // Es decir, que alcance su valor máximo de trabajo con mayor velocidad
  if (curr_ms - last_ms_PWD >= (periodoRojo / 20)) 
  {
    last_ms_PWD = curr_ms;
    nivel = (nivel + incPWD) % 256;
    analogWrite(ledRojo, nivel);
  }
}
