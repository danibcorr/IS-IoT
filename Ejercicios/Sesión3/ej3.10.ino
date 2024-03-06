#define PIR_SENSOR_PIN 3
#define LED_PIN 2

void setup() 
{
  pinMode(PIR_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() 
{
  int pirValue = digitalRead(PIR_SENSOR_PIN);
  Serial.println(pirValue);

  if (pirValue == HIGH) 
  {
    digitalWrite(LED_PIN, HIGH); 
  } 
  else 
  {
    digitalWrite(LED_PIN, LOW);   
  }

  delay(1000); 
}
