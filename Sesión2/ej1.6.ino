#define POT A0


void setup() {
  pinMode(POT, INPUT);
  Serial.begin(9600);

}

void loop() {

  int sensorValue = analogRead(POT);
  float resistencia= (sensorValue/1023.0)*10000; //calcular la resistencia. 1023 es la precisión del pin y el potenciometro=10k
  Serial.print("Valor analógico: ");
  Serial.println(resistencia);
  //delay(500);

  
}

