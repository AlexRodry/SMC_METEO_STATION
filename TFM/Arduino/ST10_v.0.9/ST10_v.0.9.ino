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
volatile bool readyToSend = false;
String telegram;
String ids[] = {"1", "2", "3", "4", "5", "6", "10"};
String sens[] = {hum, pres, temp, veleta, velo, pluvio, "rssi"};
int nids = sizeof(ids);
int i;
String SerialTelegram;
String Sep = "|";
String St = "ST01";



void setup() {
  Serial.begin(9600);                // Comunicacion serial
  Serial.println("In");
  Timer1.initialize(500000);          // Activación del timer 1 cada 500ms
  Timer1.attachInterrupt(ticks);      // Salta la función tiempo_ane a la frecuencia indicada antes
  pinMode(AnemPin,INPUT);             // Anemometro
  pinMode(PluvioPin,INPUT);           // Pluviometro
  pinMode(VelPin,INPUT);              // Veleta
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
    hum     = String(mySensor.readFloatHumidity(), 0);
    sens[0] = hum;
    pres    = String(mySensor.readFloatPressure(), 0);
    sens[1] = pres;
    temp    = String(mySensor.readTempC(), 2);
    sens[2] = temp;
    fecha   = funFecha(); 
    
    delay(50);
    //telegram = enc_telegram(sens);
    telegram = "Nombre"+Sep+St+Sep+ "Fecha"+Sep+fecha+Sep+ids[0]+Sep+sens[0]+Sep;
    Serial.println(telegram);
    readyToSend = false;
    hsControl = 2;
  }
}

String enc_telegram(){
  fecha = String(fecha);
  SerialTelegram = "Nombre"+Sep+St+Sep+ "Fecha"+Sep+fecha+Sep+sens[1]+Sep;
  /*for (i = 0; i = nids; i++){
    Serial.println(i);
    sens[i] = String(sens[i]);
    SerialTelegram = SerialTelegram + ids[i]+Sep+sens[i]+Sep;
  }
  */
  return(SerialTelegram);
}
