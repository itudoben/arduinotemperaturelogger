#include <LiquidCrystal.h>

// Setting up the data io and the 4 
LiquidCrystal lcd(12,10,5,4,3,2);

// Next step add wifi shield
// https://learn.adafruit.com/adafruit-io-basics-digital-output/arduino-wifi

// Setting the temperature sensor
const int sensorPin = A0;
const float tempBaseline = 20.0F;
const float maxSensorVal = 1024.0F;
const float pinVolt = 5.0F;
const int millivoltsPerCelsius = 10;
const float voltOffset = 0.5F;

const int delayInMillis = 15 * 1000;

// The switch to display the temperature.
const int buttonPinInput = 7;

// Setup of the arduino.
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);

  Serial.begin(9600);
  pinMode(buttonPinInput, INPUT);

  lcd.setCursor(0,0); 
  lcd.print("Temp in C");
}

//unsigned long previousMillis = 0;

// The main loop of the unique thread running.
void loop() {
  lcd.setCursor(0,0); 
  lcd.print("Temp in C");

  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  
  int switchState = digitalRead(buttonPinInput);

  // To see the serial output open in IDE Tools/Serial Monitor
  if (switchState == 1) {
    Serial.print("Button pushed: ");
    Serial.println(switchState);

    printTemperature();
  }

//  if (currentMillis - previousMillis >= delayInMillis) {
//  
//    // save the last time you blinked the LED
//    previousMillis = currentMillis;
//
//    // if the LED is off turn it on and vice-versa:
//    printTemperature();
//  }
}

// Read the temperature from the sensor.
void printTemperature() {
  int sensorVal = analogRead(sensorPin);
  
  float voltage = sensorVal / maxSensorVal * pinVolt;
  float temp = (float)(voltage - voltOffset) / millivoltsPerCelsius * 1000;

  char str[50];
  sprintf(str, "Sensor value: %i , voltage: ", sensorVal, voltage);
  Serial.print(str);
  Serial.print(voltage, DEC);
  Serial.print(" V, temperature: ");
  Serial.print(temp, DEC);
  Serial.println(" C");

  lcd.setCursor(0,1); 
  lcd.print(temp);
  delay(500);
  lcd.clear();
}
