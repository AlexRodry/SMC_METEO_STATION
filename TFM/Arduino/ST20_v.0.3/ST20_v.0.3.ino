/*.......................................................................*/
/*..........................Programa principal...........................*/
/*.......................................................................*/
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
// Inicialización de identificadores de los sensores
String ids[] = {"11", "12", "13", "20"};
// Inicialización del array de valores de los sensores (será sobreescrito)
String sens[7] = {"hum", "pres", "temp", "rssi"};
int nids = 4;                         // Número de sensores + rssi
String Sep = "|";                     // Separador empleado en el telegrama
String St = "ST02";                   // Nombre de la estación
volatile float timeSeg = 180;         // Tiempo en segundos entre envío de datos

/*Variables usadas en el SW*/
// String Reloj
String fecha;
// Handshake para enviar datos
volatile bool readyToSend = false;
// Telegrama a enviar
String SerialTelegram;
volatile float tempC;           // ToDelete
int pinLM35 = 3;                // ToDelete

void setup() {
  Serial.begin(9600);                 // Velocidad comunicacion serial
  Timer1.initialize(500000);          // Activación del timer 1 cada 500ms
  Timer1.attachInterrupt(ticks);      // Salta la función ticks a la frecuencia indicada antes
  analogReference(INTERNAL);          // Todelete

  /* Diagnosis i2C 
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
  */
}

void loop() {
  /* Espera hasta que esten todas las variables medidias */
  if (readyToSend == true){
    /* Cálculo de la humedad, presión y temperatura instantánea */
    sens[0] = "69";
    sens[1] = "96969";
    //sens[0] = String(mySensor.readFloatHumidity(), 0);
    //sens[1] = String(mySensor.readFloatPressure(), 0);
    //sens[2] = String(mySensor.readTempC(), 2);

   
    /* Obtención de la fecha en formato adecuado */
    fecha = "20200211210000";
    //fecha   = funFecha(); 
    /* Codificación del telegrama */
    SerialTelegram = encodeTelegram();
    /* Envío por puerto serie del telegrama */
    Serial.println(SerialTelegram);
    /* Handshake apagado */
    readyToSend = false;
  }
}
