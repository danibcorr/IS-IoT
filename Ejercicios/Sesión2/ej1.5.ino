#define LED_ROJO 3
#define LED_VERDE 4

const int periodo_rojo = 1024;
const int periodo_verde = 1458;
unsigned long last_ms_green = 0;
unsigned long last_ms_red = 0;
byte state_red = LOW;
byte state_green = LOW;

void setup() 
{
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
}

void loop() 
{
  // toma el tiempo actual en ms
  //millis no bloquea la ejecución
  unsigned long current_ms = millis(); 

  if((current_ms - last_ms_red) >= (periodo_rojo/2))
  {
    last_ms_red=current_ms;
    state_red=(state_red == LOW ? HIGH: LOW);
    digitalWrite(LED_ROJO, state_red);
  }

  if((current_ms - last_ms_green) >= (periodo_verde/2))
  {
    last_ms_green=current_ms;
    state_green=(state_green == LOW ? HIGH: LOW);
    digitalWrite(LED_VERDE, state_green);
  }
}