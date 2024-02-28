#define POT A0

const int max_val_pot = 10000;
const int precision = 1023;

void setup() 
{
  pinMode(POT, INPUT);
  Serial.begin(9600);

}

void loop() 
{
  int sensorValue = analogRead(POT);
  float resistencia = (sensorValue / precision) * max_val_pot; //calcular la resistencia. 1023 es la precisión del pin y el potenciometro = 10k
  Serial.print("Valor analógico: ");
  Serial.println(resistencia);
}