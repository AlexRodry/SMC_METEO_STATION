#include <RTClib.h>
#include <Wire.h>     // Comunicación I2C

RTC_DS3231 rtc;       // Declaramos un RTC DS3231

 String dia;
int mes;
 int ano;
 int hora;
 int minuto;
 int segundo;
 String fecha;

void setup() {
 Serial.begin(9600);
 delay(3000);
 // Comprobación de la conexión con el módulo RTC
 if (! rtc.begin()) {
 Serial.println("No hay un módulo RTC");
 while (1);
 }
 // Seteamos la hora con los valores de la fecha y la hora en que el sketch ha sido compilado.
 Serial.println("Test del Reloj"); 
 rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() { 
 DateTime now = rtc.now();
 
 dia = now.day();
 mes = now.month();
 ano = now.year();
 hora = now.hour();
 minuto = now.minute();
 segundo = now.second();
 fecha = (dia + '-' + mes + '-' + ano + ' ' + hora + ':' + minuto + ':' + segundo);
 Serial.println(fecha);
 delay(3000);
 /*DateTime now = rtc.now();
 Serial.print(now.day());
 Serial.print('/');
 Serial.print(now.month());
 Serial.print('/');
 Serial.print(now.year());
 Serial.print(" ");
 Serial.print(now.hour());
 Serial.print(':');
 Serial.print(now.minute());
 Serial.print(':');
 Serial.print(now.second());
 Serial.println();
 delay(3000);
 */
}
