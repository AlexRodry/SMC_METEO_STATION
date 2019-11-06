#include "SparkFunBME280.h" //Librería del sensor
#include <Wire.h>     // Comunicación I2C
BME280 mySensor;

// Strings de medida
String hum;
String pres;
String temp;

void setup() {
  Serial.begin(9600);
  Serial.println("BME280 Test");
  if (mySensor.beginI2C() == false) //Comienzo de la comunciación I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }
}

void loop() {
  
  // Convierto a String las medidas y las represento concatenando su unidad
  
  hum   = String(mySensor.readFloatHumidity(), 2);
  pres  = String(mySensor.readFloatPressure(), 0);
  temp  = String(mySensor.readTempC(), 2);
  Serial.println("Midiendo...");
  Serial.println(hum + " %");
  delay (500);
  Serial.println(pres + " Pa");
  delay (500);
  Serial.println(temp + " ºC");
  delay (500);
  
}
