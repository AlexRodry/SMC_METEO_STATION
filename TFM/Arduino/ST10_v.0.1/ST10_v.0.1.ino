#include <ArduinoJson.h>
#include "SparkFunBME280.h" //Librería del sensor
#include <Wire.h>     // Comunicación I2C
#include <RTClib.h>

RTC_DS3231 rtc;       // Declaramos un RTC DS3231 (reloj)
String fecha;
String dia;
int mes;
int ano;
int hora;
int minuto;
int segundo;

BME280 mySensor;
// Strings de medida
String hum;
String pres;
String temp;

void setup() {
  // Comprobar I2C del sensor
  Serial.begin(115200);
  if (mySensor.beginI2C() == false) //Comienzo de la comunciación I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }
 // Comprobar I2C del reloj
 if (! rtc.begin()) {
 Serial.println("No hay un módulo RTC");
 while (1);
 }
 // Seteamos la hora con los valores de la fecha y la hora en que el sketch ha sido compilado.
 rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  
  // Convierto a String las medidas y las represento concatenando su unidad
  
  hum   = String(mySensor.readFloatHumidity(), 0);
  pres  = String(mySensor.readFloatPressure(), 0);
  temp  = String(mySensor.readTempC(), 2);
  fecha = funFecha();
  delay(500);
  
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["nombre"] = "ST10";
  JsonObject& s1 = jsonBuffer.createObject();// Fecha del dato
  s1["Fecha"] = String(fecha);
  JsonObject& st = jsonBuffer.createObject(); // Tipo dato
  st["Tipo"] = "3"; //Json con 3 datos
  JsonArray& datosS1 = json.createNestedArray("Dato");
  datosS1.add(s1);
  datosS1.add(st);
  JsonObject& s3 = jsonBuffer.createObject(); // Humedad
  s3["id"] = "1";
  s3["valor"] = String(hum);
  JsonObject& s4 = jsonBuffer.createObject(); // Presion
  s4["id"] = "2";
  s4["valor"] = String(pres);
  JsonObject& s5 = jsonBuffer.createObject(); // Presion
  s5["id"] = "3";
  s5["valor"] = String(temp);
  JsonArray& datosS = json.createNestedArray("sensores");
  datosS.add(s3);
  datosS.add(s4);
  datosS.add(s5);
  json.printTo(Serial);
  Serial.println();
  /*Serial.println(hum + " %");
  delay (500);
  Serial.println(pres + " Pa");
  delay (500);
  Serial.println(temp + " ºC");
  delay (500);
  */

}

String funFecha(){
   DateTime now = rtc.now();
   String _fecha;
   char buff[14];

   dia = now.day();
   mes = now.month();
   ano = now.year();
   hora = now.hour();
   minuto = now.minute();
   segundo = now.second();
   
   sprintf(buff, "%04d%02d%02d%02d%02d%02d", ano, mes, dia, hora, minuto, segundo);
   _fecha = String(buff);
   return _fecha;
}
