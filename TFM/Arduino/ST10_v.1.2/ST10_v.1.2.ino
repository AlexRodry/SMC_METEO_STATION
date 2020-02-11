/*..................................................................................*/
/*................................Programa principal................................*/
/*..................................................................................*/
/*Librerias*/
//--Librería del sensor BME280
#include "SparkFunBME280.h"
  BME280 mySensor;
//--Libreria del reloj RTC
#include <RTClib.h>          
  RTC_DS3231 rtc;       
//--Libreria comunicacion i2C
#include <Wire.h>          
//--Interrupciones reloj
#include <TimerOne.h>
//--Librería para cálculos matemáticos
#include <math.h>          

/*Configuración y constantes*/
const int VelPin = A1;                // Seleccionar la entrada para el sensor
#define AnemPin (2)                   // Pin del Anemómetro
#define PluvioPin (3)                 // Pin del Pluviometro
// Inicialización de identificadores de los sensores
String ids[] = {"1", "2", "3", "4", "5", "6", "10"};
// Inicialización del array de valores de los sensores (será sobreescrito)
String sens[7] = {"hum", "pres", "temp", "veleta", "velo", "pluvio", "rssi"};
int nids = 7;                         // Número de sensores + rssi
String Sep = "|";                     // Separador empleado en el telegrama
String St = "ST01";                   // Nombre de la estación
volatile float timeSeg = 180;         // Tiempo en segundos entre envío de datos
float Velcte = 2.4;                   // km/h x contacto del anemómetro
float Raincte = 0.2794;               // mm de precipitación x contacto pluviómetro
// Filtro anti-rebotes por software
int DFAnem = 75;                      // 75ms para el filtro del anemómetro
int DFpluv = 75;                      // 75ms para el filtro del pluviómetro
// Calibración de la veleta
int Nort[2] = {225,400}; int NortE[2] = {141,224}; int NortO[2] = {501,675};
int Sur[2] = {676,800};  int SurE[2] = {401,500};  int SurO[2] = {801,895};
int Este[1] = {895}; int Oest[1] = {140};

/*Variables usadas en el SW*/
// String Reloj
String fecha;
// Handshake para enviar datos
volatile bool readyToSend = false;
// Telegrama a enviar
String SerialTelegram;

void setup() {
  Serial.begin(9600);                 // Velocidad comunicacion serial
  Timer1.initialize(500000);          // Activación del timer 1 cada 500ms
  Timer1.attachInterrupt(ticks);      // Salta la función ticks a la frecuencia indicada antes
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
  // Ajuste de la hora del reloj RTC
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  /* Espera hasta que esten todas las variables medidias */
  if (readyToSend == true){
    /* Cálculo de la humedad, presión y temperatura instantánea */
    sens[0] = String(mySensor.readFloatHumidity(), 0);
    sens[1] = String(mySensor.readFloatPressure(), 0);
    sens[2] = String(mySensor.readTempC(), 2);
    /* Obtención de la fecha en formato adecuado */
    fecha   = funFecha(); 
    /* Codificación del telegrama */
    SerialTelegram = encodeTelegram();
    /* Envío por puerto serie del telegrama */
    Serial.println(SerialTelegram);
    /* Handshake apagado */
    readyToSend = false;
  }
}
