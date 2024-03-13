#include <Tone.h>

Tone speaker;

const int PIR_PIN = 4;
const int SPEAKER_PIN = 3;

void setup() 
{
  pinMode(PIR_PIN, INPUT);
  speaker.begin(SPEAKER_PIN);

  Serial.begin(9600);
}

void loop() 
{
  int pirState = digitalRead(PIR_PIN);
  Serial.println(pirState);
  
  if (pirState == HIGH)
  {
    speaker.play(NOTE_A4);
  } 
  else 
  {
    speaker.stop();
  }
}
