#include <RTClib.h>         // Libreria reloj
#include <TimerOne.h>
#include <Wire.h>
#include "SparkFunBME280.h"
#include <ArduinoJson.h>
RTC_DS3231 rtc;       // Declaramos un RTC DS3231 (reloj)
String fecha;
String dia;
int mes;
int ano;
int hora;
int minuto;
int segundo;
BME280 mySensor;
// Contadores
volatile int CuentaPlu = 0;
volatile int CuentaAne = 0;
volatile int CuentaAne250ms = 0;
volatile int CuentaAne3s = 0;
volatile int CuentaAne1min = 0;
volatile int CuentaAne10min = 0;
volatile int CuentaAne1h;
volatile int CuentaAne3h;
// Variables de cálculo
volatile int MediaVel3s;
volatile float MediaVel1min = 0;
volatile float MediaVel10min;
volatile float MediaVel1h;
volatile float MediaPlu1h;
volatile float MediaPlu3h;
volatile float MediaPlu1d;
volatile float rev3s;
volatile float MediaAne3s;
volatile float MediaAne1min = 0;
volatile float MediaAne10min = 0;
volatile float MediaAne1h = 0;
// Accionadores de lectura
volatile boolean EnviarMediaAne3s = false;
volatile boolean EnviarMediaAne1min = false;
volatile boolean EnviarMediaAne10min = false;
volatile boolean EnviarMediaAne1h = false;
volatile boolean EnviarMediaPlu3h = false;
volatile boolean EnviarMediaPlu1d = false;
volatile boolean EnviarMediaVel1min = false;
volatile boolean EnviarMediaVel10min = false;
   
void setup() {
  Serial.begin(9600);
  Timer1.initialize(250000); // Salta el timer 1 cada 250 ms
  Timer1.attachInterrupt(tiempo_ane); // Salta la función tiempo_ane a la frecuencia indicada antes
  attachInterrupt(0, Ane, RISING); // Asigna la interrupción 0 (pin D2) a la función Ane cuando detecta un flanco de subida
  attachInterrupt(1, Plu, RISING); // Asigna la interrupción 1 (pin D3) a la función Plu cuando detecta un flanco de subida
  Wire.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }
}

void loop() {
    
    if (EnviarMediaAne3s == true){ // Si se activa la lectura de la media del anemómetro de 3 segundos...
      fecha = funFecha(); 
      StaticJsonBuffer<300> jsonBuffer;
      JsonObject& json = jsonBuffer.createObject();
      json["nombre"] = "Estacion";
      JsonObject& s1 = jsonBuffer.createObject();// Fecha del dato
      s1["Fecha"] = String(fecha);
      JsonObject& st = jsonBuffer.createObject(); // Tipo dato
      st["Tipo"] = "2"; //Json con 2 datos
      JsonArray& datosS1 = json.createNestedArray("Dato");
      datosS1.add(s1);
      datosS1.add(st);
      JsonObject& s3 = jsonBuffer.createObject(); // Media del anemometro cada 3s
      s3["id"] = "1";
      s3["valor"] = String(MediaAne3s);
      JsonObject& s4 = jsonBuffer.createObject(); // Media de la veleta cada 3s
      s4["id"] = "2";
      s4["valor"] = String(MediaVel3s);
      JsonArray& datosS = json.createNestedArray("sensores");
      datosS.add(s3);
      datosS.add(s4);
      json.printTo(Serial);
      Serial.println();
      EnviarMediaAne3s = false; // Se desactiva la lectura de la media del anemómetro de los 3 segundos
      MediaVel3s = 0; // Se reinicia el valor acumulado de la media de la veleta de 3 segundos
    }
  if (EnviarMediaAne1min == true){ // Si se activa la lectura del BME280...
      fecha = funFecha();
      StaticJsonBuffer<300> jsonBuffer;
      JsonObject& json = jsonBuffer.createObject();
      json["nombre"] = "Estacion";
      JsonObject& s1 = jsonBuffer.createObject();// Fecha del dato
      s1["Fecha"] = String(fecha);
      JsonObject& st = jsonBuffer.createObject(); // Tipo dato
      st["Tipo"] = "3"; //Json con 3 datos
      JsonArray& datosS1 = json.createNestedArray("Dato");
      datosS1.add(s1);
      datosS1.add(st);
      JsonObject& s3 = jsonBuffer.createObject(); // Medida de la humedad cada 1min
      s3["id"] = "3";
      s3["valor"] = String(mySensor.readFloatHumidity(), 0);
      JsonObject& s4 = jsonBuffer.createObject(); // Medida de la presión cada 1min
      s4["id"] = "4";
      s4["valor"] = String(mySensor.readFloatPressure(), 0);
      JsonObject& s5 = jsonBuffer.createObject(); // Medida de la temperatura cada 1min
      s5["id"] = "5";
      s5["valor"] = String(mySensor.readTempC(), 2);
      JsonArray& datosS = json.createNestedArray("sensores");
      datosS.add(s3);
      datosS.add(s4);
      datosS.add(s5);
      json.printTo(Serial);
      Serial.println();
      EnviarMediaAne1min = false;
    }
  if (EnviarMediaAne10min == true){ // Si se activa la lectura del anemómetro de los 10 minutos...
      fecha = funFecha(); 
      StaticJsonBuffer<300> jsonBuffer;
      JsonObject& json = jsonBuffer.createObject();
      json["nombre"] = "Estacion";
      JsonObject& s1 = jsonBuffer.createObject();// Fecha del dato
      s1["Fecha"] = String(fecha);
      JsonObject& st = jsonBuffer.createObject(); // Tipo dato
      st["Tipo"] = "2"; //Json con 2 datos
      JsonArray& datosS1 = json.createNestedArray("Dato");
      datosS1.add(s1);
      datosS1.add(st);
      JsonObject& s3 = jsonBuffer.createObject(); // Media del anemometro cada 10min
      s3["id"] = "6";
      s3["valor"] = String(MediaAne10min);
      JsonObject& s4 = jsonBuffer.createObject(); // Media de la veleta cada 10min
      s4["id"] = "7";
      s4["valor"] = String(MediaVel10min);
      JsonArray& datosS = json.createNestedArray("sensores");
      datosS.add(s3);
      datosS.add(s4);
      json.printTo(Serial);
      Serial.println();
      EnviarMediaAne10min = false; // Se desactiva la lectura de la media del anemómetro de los 10 minutos
      MediaAne10min = 0; // Se reinica el valor de la media del anemómetro de los 10 minutos
      MediaVel10min = 0; // Se reinicia la media de la veleta de 10 minutos
    }
  if (EnviarMediaAne1h == true){ // Si se activa la lectura del anemómetro de 1 hora...
      fecha = funFecha(); 
      StaticJsonBuffer<300> jsonBuffer;
      JsonObject& json = jsonBuffer.createObject();
      json["nombre"] = "Estacion";
      JsonObject& s1 = jsonBuffer.createObject();// Fecha del dato
      s1["Fecha"] = String(fecha);
      JsonObject& st = jsonBuffer.createObject(); // Tipo dato
      st["Tipo"] = "3"; //Json con 3 datos
      JsonArray& datosS1 = json.createNestedArray("Dato");
      datosS1.add(s1);
      datosS1.add(st);
      JsonObject& s3 = jsonBuffer.createObject(); // Media del anemometro cada 1h
      s3["id"] = "8";
      s3["valor"] = String(MediaAne1h);
      JsonObject& s4 = jsonBuffer.createObject(); // Media de la veleta cada 1h
      s4["id"] = "9";
      s4["valor"] = String(MediaVel1h);
      JsonObject& s5 = jsonBuffer.createObject(); // Media del pluviometro cada 1h
      s5["id"] = "10";
      s5["valor"] = String(MediaPlu1h);
      JsonArray& datosS = json.createNestedArray("sensores");
      datosS.add(s3);
      datosS.add(s4);
      datosS.add(s5);
      json.printTo(Serial);
      Serial.println();
      EnviarMediaAne1h = false; // Se desactiva la lectura de la media del anemómetro de 1 hora
      MediaAne1h = 0; // Se reinica el valor de la media del anemómetro de 1 hora
      MediaVel1h = 0; // Se reinica el valor de la media de la veleta de 1 hora
      MediaPlu1h = 0; // Se reinica el valor de la media del pluviómetro de 1 hora
    }
  if (EnviarMediaPlu3h == true){ // Si se activa la lectura de la media del pluviómetro de las 3 horas...
      fecha = funFecha();
      StaticJsonBuffer<300> jsonBuffer;
      JsonObject& json = jsonBuffer.createObject();
      json["nombre"] = "Estacion";
      JsonObject& s1 = jsonBuffer.createObject();// Fecha del dato
      s1["Fecha"] = String(fecha);
      JsonObject& st = jsonBuffer.createObject(); // Tipo dato
      st["Tipo"] = "1"; //Json con 1 datos
      JsonArray& datosS1 = json.createNestedArray("Dato");
      datosS1.add(s1);
      datosS1.add(st);
      JsonObject& s3 = jsonBuffer.createObject(); // Media del pluviometro cada 3h
      s3["id"] = "11";
      s3["valor"] =  String(MediaPlu3h); 
      JsonArray& datosS = json.createNestedArray("sensores");
      datosS.add(s3);
      json.printTo(Serial);
      Serial.println();
      EnviarMediaPlu3h = false; // Se desactiva la lectura de la media del pluviómetro de las 3 horas
      MediaPlu3h = 0; // Se reinicia el valor de la media del pluviómetro de las 3 horas
   }
  if (EnviarMediaPlu1d == true){ // Si se activa la lectura de la media del pluviómetro de 1 día...
      fecha = funFecha(); 
      StaticJsonBuffer<300> jsonBuffer;
      JsonObject& json = jsonBuffer.createObject();
      json["nombre"] = "Estacion";
      JsonObject& s1 = jsonBuffer.createObject();// Fecha del dato
      s1["Fecha"] = String(fecha);
      JsonObject& st = jsonBuffer.createObject(); // Tipo dato
      st["Tipo"] = "1"; //Json con 1 datos
      JsonArray& datosS1 = json.createNestedArray("Dato");
      datosS1.add(s1);
      datosS1.add(st);
      JsonObject& s3 = jsonBuffer.createObject(); // Media del pluviometro cada 1 dia
      s3["id"] = "12";
      s3["valor"] = String(MediaPlu1d); 
      JsonArray& datosS = json.createNestedArray("sensores");
      datosS.add(s3);
      json.printTo(Serial);
      Serial.println();
      EnviarMediaPlu1d = false; // Se desactiva la lectura de la media del pluviómetro de 1 día
      MediaPlu1d = 0; // Se reinicia la media del pluviómetro de 1 día
    }
  
}

void tiempo_ane(){
  CuentaAne250ms++; // Se incrementa la variable cuendo se activa la función, es decir, cada 250 milisegundos
  if (CuentaAne250ms == 12){ // Cuando el timer alcanza 12 pulsos (3 segundos)...
    // ------------ Anemómetro ---------------
    CuentaAne3s++; // Se aumenta el contador de 3 segundos
    rev3s = ((float)CuentaAne)/(2*3); // Se calcula el número de revoluciones por segundo que se han medido en los 3 segundos (teniendo en cuenta que hay dos pulsos por vuelta)
    MediaAne3s = 2.4*rev3s; // Se realiza la equivalencia de revoluciones por segundo a kilómetros por hora. 1 revolución por segundo corresponde a 2.4 km/h
    EnviarMediaAne3s = true; // Se activa la lectura de la media de los 3 segundos
    MediaAne1min = MediaAne1min + MediaAne3s; // Se acumula el valor de las medias de 3 segundos para hacer una media de los 10 minutos
    CuentaAne250ms = 0; // La cuenta de 250 milisegundos se reinicia
    CuentaAne = 0; // Se reinicia la cuenta de vueltas del anemómetro
    // ------------ Veleta ---------------
    MediaVel3s = veleta(); // Se lee la veleta y se devuelve el valor de los grados respecto al norte
    MediaVel1min = MediaVel3s + MediaVel1min; // Se acumulan los valores de los grados para hacer la media de la veleta en 1 minuto
  }
  if (CuentaAne3s == 20){ // Cuando la cuenta del anemómetro llegue a 20, es decir, 1 minuto...
    // ------------ Anemómetro ---------------
    CuentaAne1min++; // Se incrementa el contador del anemómetro de 1 minuto
    CuentaAne3s = 0; // Se reinicia el contador del anemómetro de 3 segundos
    MediaAne1min = MediaAne1min/20; // Se hace la media de la velocidad del anemómetro en 1 minuto
    MediaAne10min = MediaAne10min + MediaAne1min; // Se acumulan los valores del anemómetro de cada minuto para hacer la media de cada 10 minutos
    MediaAne1min = 0; // Se reinicia la media del anemómetro de 1 minuto
    // ------------ Veleta ---------------
    MediaVel1min = MediaVel1min/20; // Se calcula la media de la veleta de 1 minuto respecto a los 20 datos obtenidos
    MediaVel10min = MediaVel10min + MediaVel1min; // Se acumulan valores de la media de la veleta de 1 minuto para calcular la media de 10 minutos
    MediaVel1min = 0; // Se reinicia la media de la veleta de 1 minuto
    // ------------ BME280 ---------------
    EnviarMediaAne1min = true;
  }
  if (CuentaAne1min == 10){ // Cuando la cuenta del anemómetro de 1 minuto llega a 10, es decir, a 10 minutos...
    // ------------ Anemómetro ---------------
    CuentaAne10min++; // Se incrementa el contador de los 10 minutos
    MediaAne10min = MediaAne10min/10; // Se hace la media de los 10 valores acumulados de la media del anemómetro de 1 minuto
    MediaAne1h = MediaAne1h + MediaAne10min; // Se acumula el valor medio del anemómetro de cada 10 minutos para calcular la media del anemómetro de cada hora
    EnviarMediaAne10min = true; // Se activa la lectura de la media de los 10 minutos
    CuentaAne1min = 0; // Se reinicia la cuenta del anemómetro de 1 minuto
    // ------------ Veleta ---------------
    MediaVel10min = MediaVel10min/10; // Se hace la media de los 10 valores de la media de 1 minuto acumulados
    MediaVel1h = MediaVel1h + MediaVel10min; // Se acumulan las medias de 10 minutos de la veleta para hacer la media de la veleta de 1 hora
  }
  if (CuentaAne10min == 6){ // Cuando la cuenta de los 10 minutos ha llegado a 6, es decir, a 1 hora...
    // ------------ Anemómetro ---------------
    CuentaAne1h++; // Se incrementa el contador de 1 hora
    MediaAne1h = MediaAne1h/6; // Se hace la media de los 6 valores acumulados de la media de 10 minutos
    EnviarMediaAne1h = true; // Se activa la lectura de la media de la hora
    CuentaAne10min = 0; // Se reinicia la cuenta de los 10 minutos
    // ------------ Veleta ---------------
    MediaVel1h = MediaVel1h/6; // Se hace la media de los 6 datos de la media de 10 minutos acumulados de la veleta
    // ------------ Pluviómetro ---------------
    MediaPlu1h = ((float)CuentaPlu)*0.2794; // 0.2794 mm por pulso;
    MediaPlu3h = MediaPlu3h + MediaPlu1h; // Se acumulan los valores del pluviómetro
  }
  if (CuentaAne1h == 3){ // Si el contador del anemómetro de 1 hora llega a 3, es decir, a las 3 horas..
    CuentaAne3h++; // Se incrementa el contador del anemómetro de las 3 horas
    CuentaAne1h = 0; // Se reinicia el contador del anemómetro de 1 hora
    // ------------ Pluviómetro ---------------
    MediaPlu1d = MediaPlu1d + MediaPlu3h; // Se acumulan los valores del pluviómetro
    EnviarMediaPlu3h = true; // Se activa la lectura de la media del pluviómetro de las 3 h
  }
  if(CuentaAne3h == 8){ // Si la cuenta del anemómetro de 3 horas llega a 8, es decir, 1 día...
    CuentaAne3h = 0; // Se reinicia la cuenta del anemómetro de las 3 horas
    // ------------ Pluviómetro ---------------
    EnviarMediaPlu1d = true; // Se activa la lectura del pluviómetro de la media de 1 día
  }
}


// Cuando la interrupción 0 detecta un flanco de subida se activa la función Ane()
// que lo único que hace es aumentar un contador
void Ane(){
  CuentaAne++; // Se incrementa el número de pulsos detectados
}

// La función veleta lee el estado de la veleta y devuelve su posición en grados
int veleta(){
  int a = analogRead(1);
  if ((a>=850)&&(a<=900)){
    return 0;
  }
  else if ((a>=45)&&(a<=55)){
    return 180;
  }
  else if ((a>=160)&&(a<=190)){
    return 270;
  }
  else if ((a>=610)&&(a<=660)){
    return 90;
  }
  else if ((a>=760)&&(a<=800)){
    return 45;
  }
  else if ((a>=430)&&(a<=470)){
    return 315;
  }
  else if ((a>=90)&&(a<=110)){
    return 225;
  }
  else if ((a>=280)&&(a<=310)){
    return 135;
  }
  else if ((a>=670)&&(a<=710)){
    return 22;
  }
  else if ((a>=510)&&(a<=550)){
    return 67;
  }
  else if ((a>=240)&&(a<=260)){
    return 112;
  }
  else if ((a>=40)&&(a<=44)){
    return 157;
  }
  else if ((a>=30)&&(a<=35)){
    return 202;
  }
  else if ((a>=60)&&(a<=70)){
    return 252;
  }
  else if ((a>=130)&&(a<=145)){
    return 292;
  }
  else if ((a>=400)&&(a<=435)){
    return 337;
  }
}


// La función Plu está ligada a la interrupción 1 que mide la lluvia.
// Lo que hace la función es contar pulsos.
unsigned long tiempo;
void Plu(){
  if(micros() - tiempo > 100){
    CuentaPlu++;
    tiempo = micros();
  }
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
