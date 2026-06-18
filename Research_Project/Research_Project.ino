#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const int analogPin = A0;
const int sampleSize = 10;

int values[sampleSize];

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
}

void loop()
{
  // Collect samples
  for(int i=0;i<sampleSize;i++)
  {
    values[i] = analogRead(analogPin);
    delay(5);
  }

  // Sort values (simple bubble sort)
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

  // Median value
  int medianADC = values[sampleSize/2];

  // Convert ADC to voltage
  float voltage = medianADC * (5.0 / 1023.0);

  // Convert voltage to 0–50 scale
  int result1 = voltage * 10.0;
  int result2 = 0;

  // Serial Monitor
  Serial.print("Median ADC: ");
  Serial.print(medianADC);

  Serial.print("  Voltage: ");
  Serial.print(voltage,3);

  Serial.print(" V  Scale: ");
  Serial.println(result1);

  // LCD Output
  lcd.setCursor(0,0);
  lcd.print("RESULT 1: ");
  lcd.print(result1);
  lcd.print("   ");

  lcd.setCursor(0,1);
  lcd.print("RESULT 2: ");
  lcd.print(result2);
  lcd.print("   ");

  delay(1000);
}