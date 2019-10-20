#include <ArduinoJson.h>
#include "SparkFunBME280.h" //Librería del sensor
#include <Wire.h>           // Comunicación I2C
#include <RTClib.h>         // Libreria reloj
#include <math.h>           // Librería para cálculos con el anemóemtro
// ---Reloj
RTC_DS3231 rtc;       // Declaramos un RTC DS3231 (reloj)
String fecha;
String dia;
int mes;
int ano;
int hora;
int minuto;
int segundo;

// ---P,T y H
BME280 mySensor;
// Strings de medida
String hum;
String pres;
String temp;

// ---Veleta, anemómetro y pluviómetro
const int sensorPin = A1; // Seleccionar la entrada para el sensor
int sensorValue;          // Variable que almacena el valor raw (0 a 1023)
String veleta;            // Dirección que marca la veleta 

// ---Anemometro
//#define AnemPin (2)                   // Pin del Anemómetro //ARP Puenteado (sensor no disponible)
bool AnemPin;                         // ARP Sustitucion del sensor
volatile unsigned long Rots;          // Contador nº de giros
volatile unsigned long DebounceTime1;  // Temporizador para evitar el rebote del contacto 
float Velo;                           // Velocidad km/h 
float TimeMedia1 = 3000;               // Tiempo a realizar la media  
float Velcte  = 2.4;                  // km/h x rev

#define PluvioPin (3)                 // Pin del Pluviómetro
volatile unsigned long Contactos;     // Contador nº de Contactos
volatile unsigned long DebounceTime2;  // Temporizador para evitar el rebote del contacto 
float Lluvia;                         // Precipitaciones mm
float TimeMedia2 = 3000;               // Tiempo a realizar la media  
float Raincte  = 0.2794;              // mm x contacto

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
 // Configuración interrupción del anemómetro
 //pinMode(AnemPin, INPUT); 
 attachInterrupt(digitalPinToInterrupt(AnemPin), rot_count, RISING); 
}

void loop() {
  
  // Convierto a String las medidas y las represento concatenando su unidad
  
  hum   = String(mySensor.readFloatHumidity(), 0);
  pres  = String(mySensor.readFloatPressure(), 0);
  temp  = String(mySensor.readTempC(), 2);
  fecha = funFecha();
  
  sensorValue = analogRead(sensorPin);       // Realiza la lectura
  veleta = direction(sensorValue);           // Se procesa el valor Raw con una función

  Rots = 0;               // Inicializar a 0 las vuelta
  sei();                  // Habilitar interrupciones 
  AnemPin = random(0,2);  // ARPSustitucion sensor
  delay (TimeMedia1);     // Espera del tiempo para hacer la media 
  cli();                  // Deshabilitar interrupcione
  Velo = (Rots * Velcte)/(TimeMedia1*0.001);

  Contactos = 0;          // Inicializar a 0 los contactos 
  sei();                  // Habilitar interrupciones 
  delay (TimeMedia2);     // Espera del tiempo para hacer la media 
  cli();                  // Deshabilitar interrupciones  
  Lluvia = (Contactos * Raincte)/(TimeMedia2/1000);

  delay(500);
  
  StaticJsonBuffer<3000> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["nombre"] = "ST10";
  JsonObject& s1 = jsonBuffer.createObject();// Fecha del dato
  s1["Fecha"] = String(fecha);
  JsonObject& st = jsonBuffer.createObject(); // Tipo dato
  st["Tipo"] = "6"; //Json con 6 datos
  JsonArray& datosS1 = json.createNestedArray("Dato");
  datosS1.add(s1);
  datosS1.add(st);
  JsonObject& s3 = jsonBuffer.createObject(); // Humedad
  s3["id"] = "1";
  s3["valor"] = String(hum);
  JsonObject& s4 = jsonBuffer.createObject(); // Presion
  s4["id"] = "2";
  s4["valor"] = String(pres);
  JsonObject& s5 = jsonBuffer.createObject(); // Temperatura
  s5["id"] = "3";
  s5["valor"] = String(temp);
  JsonObject& s6 = jsonBuffer.createObject(); // Direccion
  s6["id"] = "4";
  s6["valor"] = String(veleta);
  JsonObject& s7 = jsonBuffer.createObject(); // Velocidad
  s7["id"] = "5";
  s7["valor"] = String(Velo);
  JsonObject& s8 = jsonBuffer.createObject(); // Lluvia
  s8["id"] = "6";
  s8["valor"] = String(Lluvia);
  JsonArray& datosS = json.createNestedArray("sensores");
  datosS.add(s3);
  datosS.add(s4);
  datosS.add(s5);
  datosS.add(s6);
  datosS.add(s7);
  datosS.add(s8);
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
// ---Funciones
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
String direction(int a)
{
  if ((a>=225)&&(a<=400)){
    return "N";
  }
  else if ((a>=501)&&(a<=675)){
    return "NE";
  }
  else if ((a>=676)&&(a<=800)){
    return "S";
  }
  else if ((a>=801)&&(a<=895)){
    return "SE";
  }
  else if (a>=895){
    return "E";
  }
  else if ((a>=401)&&(a<=500)){
    return "SO";
  }
  else if (a<=140){
    return "O";
  }
  else if ((a>=141)&&(a<=224)){
    return "NO";
  }
}
// Función que incrementa el número de rotaciones
void rot_count () { 

if ((millis() - DebounceTime1) > 15 ) { // Debounce con 15ms. 
Rots++; 
DebounceTime1 = millis(); 
} 

}

// Función que incrementa el número de contactos
void contact_count () {   
  if ((millis() - DebounceTime2) > 30 ) { // Debounce con 30ms. 
  Contactos++; 
  DebounceTime2 = millis(); 
  } 
}
