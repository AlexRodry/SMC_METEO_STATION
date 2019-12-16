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
// Handshake Lopy
int hsControl = 1;
int HSinput   = 7;
int HSoutput  = 8;


void setup() {
  Serial.begin(9600);         // Comunicacion serial
  pinMode(AnemPin,INPUT);       // Anemometro
  pinMode(PluvioPin,INPUT);     // Pluviometro
  pinMode(VelPin,INPUT);        // Veleta
  pinMode(HSinput,INPUT);       // Input handshake
  pinMode(HSoutput,OUTPUT);     // Output handshake
  // Configuracion interrupciones
  attachInterrupt(digitalPinToInterrupt(AnemPin), rot_count, RISING);
  attachInterrupt(digitalPinToInterrupt(PluvioPin), pluv_count, RISING); 
  // Diagnosis i2C 
  if (! mySensor.beginI2C() || ! rtc.begin())
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

  if (hsControl == 1){
    digitalWrite(HSoutput, HIGH);
    json_telegram();
    delay(500);
    digitalWrite(HSoutput, LOW); 
    if (digitalRead(HSinput) == HIGH){
      Serial.println("Caso 1 a 2");
      hsControl = 2; 
    }
  }
  else if (hsControl == 2){
    if (digitalRead(HSinput) == LOW){
      hsControl = 1; 
    }
  }
}
