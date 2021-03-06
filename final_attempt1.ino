#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);// Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)

#define lm35 A0
#define vibra A1
#define levelsens A2
boolean sendsms1 = false;
boolean sendsms2 = false;
boolean sendsms3 = false;

int temp, value;
int levelvalue;
int vibrationvalue;
int temperature;


byte degree[8] = { 0b00011, 0b00011, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000 };

void setup()

{
  Serial.begin(9600); //Initialise serial to communicate with GSM Modem
  delay(100);
  pinMode(lm35, INPUT);
  pinMode(vibra, INPUT);
  pinMode(levelsens, INPUT);
  lcd.begin(16, 2);
  delay(1000);
  lcd.createChar(1, degree);
  lcd.setCursor(0, 0);
  lcd.print("Bridge Health");
  lcd.setCursor(0, 1);
  lcd.print("Monitering");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("B.E PROJECT");
  lcd.setCursor(0, 1);
  lcd.print("By Vaibhav Pawar");
  delay(1000);
  lcd.clear();
  delay(1000);
}
void loop()
{
  value = analogRead(lm35);//LM35 temperature sensor calibration
  temp = (value / 1024.0) * 25;
  delay(500);
  vibrationvalue = analogRead(vibra);
  delay(500);
  levelvalue = analogRead(levelsens);
  delay(1000); //Give enough time for GSM to register on Network
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("temperature");
  lcd.setCursor(0, 1);
  lcd.print(temp); // temperature data on LCD
  lcd.print(" C");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(vibrationvalue);
  lcd.setCursor(0, 1);
  lcd.print("vibration"); // Vibration data on LCD
  lcd.write(1);
  lcd.print(" Hz");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Level");
  lcd.setCursor(0, 1);
  lcd.print(levelvalue); // Level data on LCD
  lcd.print(" cm");
  delay(1000);
  lcd.clear();

  if
  (temp > 5)
  {
    sendsms1 = true; // SMS for temperature high
  }
  else
  {
    sendsms1 = false;
  }
  if (vibrationvalue > 900)
  {
    sendsms2 = true; // SMS for vibration high
  }
  else
  {
    sendsms2 = false;
  }

  if (levelvalue > 600)
  {
    sendsms3 = true; // SMS for Close water level
  }
  else
  { sendsms3 = false;
  }

  if (sendsms1)
  {
    Serial.println("AT+CMGF=1"); //To send SMS in Text Mode
    delay(500);
    Serial.println("AT+CMGS=\"+919604724852\"\r"); //Change to destination phone number
    delay(500);
    Serial.print("Very High,");
    Serial.print(" Temperature at bridge ");
    Serial.print(temp);
    Serial.println(" C");
    Serial.println((char)26); //the stopping character Ctrl+Z
    lcd.setCursor(0, 0);
    lcd.print("Very high ");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature");
    lcd.setCursor(0, 1);
    lcd.print(temp);
    lcd.print(" C");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sending SMS");
    delay(1000);
    lcd.clear();
    delay(10);
  }
  if (sendsms2)
  {
    delay(1000);
    Serial.println("AT+CMGF=1");
    delay(500);
    Serial.println("AT+CMGS=\"+919604724852\"\r");
    delay(500);
    Serial.print("Bridge vibrating, ");
    Serial.print(" vibration ");
    Serial.print(vibrationvalue);
    Serial.println(" Hertz");
    Serial.println((char)26);
    lcd.setCursor(0, 0);
    lcd.print("Vibration High ");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("vibration");
    lcd.setCursor(0, 1);
    lcd.print(vibrationvalue);
    lcd.write(1);
    lcd.print("Hz");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sending SMS");
    delay(1000);
    lcd.clear();
    delay(10);
  }

  if (sendsms3)
  {
    delay(1000);
    Serial.println("AT+CMGF=1");
    delay(500);
    Serial.println("AT+CMGS=\"+919604724852\"\r");
    delay(500);
    Serial.print("High level,");
    Serial.print(" of water,");
    Serial.print(levelvalue);
    Serial.println(" cm");
    Serial.println((char)26);
    lcd.setCursor(0, 0);
    lcd.print("High level");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("of Water, ");
    lcd.setCursor(0, 1);
    lcd.print(levelvalue);
    lcd.print("  cm");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sending SMS");
    delay(1000);
    lcd.clear();
    delay(10);
  }
}
