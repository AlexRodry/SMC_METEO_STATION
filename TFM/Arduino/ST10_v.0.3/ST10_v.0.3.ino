/*Librerias*/
//--Sensor BME280
#include "SparkFunBME280.h" //Librería del sensor
BME280 mySensor;
//--Comunicacion i2C
#include <Wire.h>           //Comunicación I2C

/*Variables*/
// Strings de medida BME280
String hum;
String pres;
String temp;
// String anemometro
String velo;
#define AnemPin (2)                   // Pin del Anemómetro
/*Puenteo de interrupciones*/
int pinAnemInt = 7;
boolean valor;

void setup() {
  Serial.begin(9600);
  pinMode(pinAnemInt,OUTPUT);
  pinMode(AnemPin,INPUT);
  attachInterrupt(AnemPin, rot_count, RISING); // Asigna la interrupción 0 (pin D2) a la función Ane cuando detecta un flanco de subida  
  if (mySensor.beginI2C() == false) //Comienzo de la comunciación I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }
}

void loop() {

  velo = anem();
  Serial.println(velo);

}
