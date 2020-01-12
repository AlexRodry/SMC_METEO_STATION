/*Librerias*/
//--Sensor BME280
#include "SparkFunBME280.h" // Librería del sensor
  BME280 mySensor;
//--Reloj RTC
#include <RTClib.h>         // Libreria del reloj RTC
  RTC_DS3231 rtc;       
//--Comunicacion i2C
#include <Wire.h>           // Comunicación I2C
//--Interrupciones reloj
#include <TimerOne.h>

/*Variables*/
// Sensor BME280
String hum;
String pres;
String temp;
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
bool readyToSend = false;


void setup() {
  Serial.begin(57600);                // Comunicacion serial
  Serial.println("In");
  Timer1.initialize(500000);          // Activación del timer 1 cada 500ms
  Timer1.attachInterrupt(ticks);      // Salta la función tiempo_ane a la frecuencia indicada antes
  pinMode(AnemPin,INPUT);             // Anemometro
  pinMode(PluvioPin,INPUT);           // Pluviometro
  pinMode(VelPin,INPUT);              // Veleta
  pinMode(HSinput,INPUT);             // Input handshake
  pinMode(HSoutput,OUTPUT);           // Output handshake
  // Configuracion interrupciones
  attachInterrupt(digitalPinToInterrupt(AnemPin), rot_count, RISING);
  attachInterrupt(digitalPinToInterrupt(PluvioPin), pluv_count, RISING); 
  // Diagnosis i2C 
  if (! mySensor.beginI2C() || ! rtc.begin())
  {
    Serial.println("The sensors did not respond. Please check wiring.");
    while(1); //Freeze
  }
  else{
    Serial.println("i2C OK");
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  if (readyToSend == true){
    digitalWrite(HSoutput,HIGH);
    hum     = String(mySensor.readFloatHumidity(), 0);
    pres    = String(mySensor.readFloatPressure(), 0);
    temp    = String(mySensor.readTempC(), 2);
    fecha   = funFecha(); 
    delay(50);
    json_telegram();
    readyToSend = false;
    hsControl = 2;
  }
}
