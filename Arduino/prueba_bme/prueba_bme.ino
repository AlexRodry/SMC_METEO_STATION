#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;
#include <TimerOne.h>
#include <Wire.h>
#include "SparkFunBME280.h"
BME280 mySensor;

boolean Enviar = false;

void setup() {
  Serial.begin(9600);
  Timer1.initialize(10000000); // Salta el timer 1 cada 250 ms
  Timer1.attachInterrupt(tiempo_ane); // Salta la función tiempo_ane a la frecuencia indicada antes
  Wire.begin();
  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }
  clock.begin();
  clock.setDateTime(2019,04,05,9,10,00);
}

void loop() {
  if (Enviar == true){
    Serial.print("Humidity:");Serial.print(mySensor.readFloatHumidity(), 0);Serial.print("/Pressure:");Serial.print(mySensor.readFloatPressure(), 0);
    Serial.print("/Alt:");Serial.print(mySensor.readFloatAltitudeMeters(), 1);Serial.print("/Temp:");Serial.println(mySensor.readTempC(), 2);
    dt = clock.getDateTime();
    Serial.print(dt.year);Serial.print("-");Serial.print(dt.month);Serial.print("-");Serial.print(dt.day);Serial.print("/");
    Serial.print(dt.hour);Serial.print(":");Serial.print(dt.minute);Serial.print(":");Serial.println(dt.second);
    Enviar = false;
  }

}

void tiempo_ane(){
  Enviar = true;
}
