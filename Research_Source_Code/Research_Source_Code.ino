#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const int analogPin = A0;  
const int analogPin2 = A1; 
const int sampleSize = 10;

int values[sampleSize];
int values2[sampleSize];   

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
}

void loop()
{
  // Collect samples for both pins simultaneously
  for(int i=0;i<sampleSize;i++)
  {
    values[i] = analogRead(analogPin);
    values2[i] = analogRead(analogPin2); // Sample from A1
    delay(5);
  }

  // Sort values for Result 1 (A0) using bubble sort
  for(int i=0;i<sampleSize-1;i++)
  {
    for(int j=i+1;j<sampleSize;j++)
    {
      if(values[j] < values[i])
      {
        int temp = values[i];
        values[i] = values[j];
        values[j] = temp;
      }
    }
  }

  // Sort values for Result 2 (A1) using bubble sort
  for(int i=0;i<sampleSize-1;i++)
  {
    for(int j=i+1;j<sampleSize;j++)
    {
      if(values2[j] < values2[i])
      {
        int temp = values2[i];
        values2[i] = values2[j];
        values2[j] = temp;
      }
    }
  }

  // Calculate Median values for both signals
  int medianADC = values[sampleSize/2];
  int medianADC2 = values2[sampleSize/2];

  // Convert ADC to voltage (0.0 to 5.0 V)
  float voltage = medianADC * (5.0 / 1023.0);
  float voltage2 = medianADC2 * (5.0 / 1023.0);

  // Convert voltage to 0–50 scale
  int result1 = voltage * 10.0;
  int result2 = voltage2 * 10.0; 

  // Serial Monitor Output
  Serial.print("R1 - Median ADC: ");
  Serial.print(medianADC);
  Serial.print("  Voltage: ");
  Serial.print(voltage,3);
  Serial.print(" V  Scale: ");
  Serial.print(result1);

  Serial.print("  |  R2 - Median ADC: ");
  Serial.print(medianADC2);
  Serial.print("  Voltage: ");
  Serial.print(voltage2,3);
  Serial.print(" V  Scale: ");
  Serial.println(result2);

  // LCD Output
  lcd.setCursor(0,0);
  lcd.print("RESULT 1: ");
  lcd.print(result1);
  lcd.print("    "); 

  lcd.setCursor(0,1);
  lcd.print("RESULT 2: ");
  lcd.print(result2);
  lcd.print("    "); 

  delay(1000);
}