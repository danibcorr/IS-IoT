const int pinLED = 3;
const int v_in = 5; // volts
int val = 0;
float v_out = 0;
const int r_1 = 10000; // resistence 10K → 1k

void setup() 
{
  pinMode(pinLED, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  val = analogRead(0);
  v_out = 5.0 * val / 1023.0; // convert to volts
  // Rphoto = R1 * (Vin - Vout)/Vout
  float r_ph = r_1 * (v_in - v_out)/v_out;
  Serial.println(v_out); 
  Serial.println(r_ph);

  if(v_out < 2.5)
  {
    digitalWrite(pinLED, HIGH);
  } 
  else 
  {
    digitalWrite(pinLED, LOW); 
  }

  delay(1000);
}
