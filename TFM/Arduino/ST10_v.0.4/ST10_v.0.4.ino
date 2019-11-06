/*Librerias*/
//--Sensor BME280
#include "SparkFunBME280.h" // Librería del sensor
  BME280 mySensor;
//--Reloj RTC
#include <RTClib.h>         // Libreria del reloj RTC
  RTC_DS3231 rtc;       
//--Comunicacion i2C
#include <Wire.h>           // Comunicación I2C

/*Variables*/
// Sensor BME280
String hum;
String pres;
String temp;
String counts[1];
// Anemometro
String velo;
#define AnemPin (2)                   // Pin del Anemómetro
// Pluviometro
String pluvio;
#define PluvioPin (3)                 // Pin del Pluviometro
// Veleta
const int VelPin = A1;                // Seleccionar la entrada para el sensor
String veleta;                        // Dirección que marca la veleta 
// String Reloj
String fecha;

void setup() {
  Serial.begin(9600);
  pinMode(AnemPin,INPUT);
  pinMode(PluvioPin,INPUT);
  pinMode(VelPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(AnemPin), rot_count, RISING);
  attachInterrupt(digitalPinToInterrupt(PluvioPin), pluv_count, RISING);  
  if (! mySensor.beginI2C() || ! rtc.begin())//Comienzo de la comunciación I2C
  {
    Serial.println("The sensors did not respond. Please check wiring.");
    while(1); //Freeze
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  ticks();
  veleta  = direcc();
  hum     = String(mySensor.readFloatHumidity(), 0);
  pres    = String(mySensor.readFloatPressure(), 0);
  temp    = String(mySensor.readTempC(), 2);
  fecha   = funFecha();
  /*Serial.println(velo);
  Serial.println(pluvio);
  Serial.println(veleta);
  Serial.println(hum);
  Serial.println(pres);
  Serial.println(temp);
  Serial.println(fecha);*/
  delay(200);
  json_telegram();
}
