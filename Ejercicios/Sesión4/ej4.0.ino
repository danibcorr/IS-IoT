const int pinLDR = A0;

int valorLDR;       // Valor leído del LDR
int minLDR = 1023;  // Valor mínimo leído del LDR
int maxLDR = 0;     // Valor máximo leído del LDR

void setup() 
{
    Serial.begin(9600);
}

void loop() 
{
    valorLDR = analogRead(pinLDR);

    // Actualiza los valores mínimo y máximo
    if (valorLDR > maxLDR) 
    {
        maxLDR = valorLDR;
    } 
    else if (valorLDR < minLDR) 
    {
        minLDR = valorLDR;
    }

    Serial.print("Valor LDR: ");
    Serial.println(valorLDR);
    Serial.print("Min LDR: ");
    Serial.println(minLDR);
    Serial.print("Max LDR: ");
    Serial.println(maxLDR);
    Serial.println();

    delay(1000);
}
