#include<SoftwareSerial.h>
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 6, 5, 4); //initialise the LCD module

float V, P;
const int sensorIn = 2; //input pin for current sensor
int a, mVperAmp = 186; // use 100 for 20A Module and 66 for 30A Module

byte block[8] = {            // defining the custom character
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

double Voltage = 0;    //Variable for the voltage reading from the
float VRMS = 0;   // Variable for the calculation of AmpsRMS
float AmpsRMS = 0;  //RMS reading from the sensor
SoftwareSerial firebase(2, 3);

int i;
void setup()
{

  lcd.begin(16, 2);    //Starting the lcd module
  Serial.begin(9600);  // initialising the serial port
  firebase.begin(115200);  //initialising the ESP8266 Node MCU
  lcd.setCursor(0, 0);
  lcd.print("Waiting for WiFi");    //starting the wifi
  lcd.createChar(1, block);



  for (i = 0; i <= 15; i++)
  {
    lcd.setCursor(i, 1);
    lcd.write(1);
    delay(625);
  }
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("V:");
  lcd.setCursor(0, 1);
  lcd.print("A:");
  lcd.setCursor(8, 1);
  lcd.print("P:");
}


void loop()
{
  a = analogRead(0);
  V = map(a, 0, 1084, 0, 230);
  Serial.println(V);
  firebase.println(V);
  lcd.setCursor(6, 0);
  lcd.print(V);
  Voltage = getVPP();
  VRMS = (Voltage / 2.0) * 0.707;
  AmpsRMS = (VRMS * 1000) / mVperAmp;
  Serial.println(AmpsRMS);
  firebase.println(AmpsRMS);
  lcd.setCursor(2, 1);
  lcd.print(AmpsRMS);
  P = V * AmpsRMS;
  lcd.setCursor(10, 1);
  lcd.print(P);
  delay(700);

  delay(10000);
}

float getVPP()
{
  float result;

  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;       // store min value here

  uint32_t start_time = millis();
  while ((millis() - start_time) < 1000) //sample for 1 Sec
  {
    readValue = analogRead(sensorIn);
    // see if you have a new maxValue
    if (readValue > maxValue)
    {
      /*record the maximum sensor value*/
      maxValue = readValue;
    }
    if (readValue < minValue)
    {
      /*record the maximum sensor value*/
      minValue = readValue;
    }
  }

  // Subtract min from max
  result = ((maxValue - minValue) * 5.0) / 1024.0; //returning the RMS power

  return result;
}
