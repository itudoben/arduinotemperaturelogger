// Next step add wifi shield
// https://learn.adafruit.com/adafruit-io-basics-digital-output/arduino-wifi

const int sensorPin = A0;
const float tempBaseline = 20.0F;
const float maxSensorVal = 1024.0F;
const float pinVolt = 5.0F;
const int millivoltsPerCelsius = 10;
const float voltOffset = 0.5F;

const int delayInMillis = 15 * 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, INPUT);
}

unsigned long previousMillis = 0;

void loop() {
  // put your main code here, to run repeatedly:
    unsigned long currentMillis = millis();

    int switchState = digitalRead(2);
    
    if (switchState == 1) {
      Serial.print("Button pushed: ");
      Serial.println(switchState);

      printTemperature();
    }

  if (currentMillis - previousMillis >= delayInMillis) {
  
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
     printTemperature();
  }
}

void printTemperature() {
  int sensorVal = analogRead(sensorPin);
  
  float voltage = sensorVal / maxSensorVal * pinVolt;
  float temp = (float)(voltage - voltOffset) / millivoltsPerCelsius * 1000;

  char str[50];
  sprintf(str, "Sensor value: %i , voltage: ", sensorVal);
  Serial.print(str);
  Serial.print(voltage, DEC);
  Serial.print(" V, temperature: ");
  Serial.print(temp, DEC);
  Serial.println(" C");
}


