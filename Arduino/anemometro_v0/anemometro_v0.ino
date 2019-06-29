#include <DS3231.h>
DS3231 clock;
//RTCDateTime dt;
#include <TimerOne.h>
#include <Wire.h>
#include "SparkFunBME280.h"
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
  clock.begin();
  clock.setDateTime(2019,04,05,9,10,00);
  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }
}

void loop() {
  
    if (EnviarMediaAne3s == true){ // Si se activa la lectura de la media del anemómetro de 3 segundos...
    // ------------ Anemómetro ---------------
    Serial.print("Media anemometro 3s: "); // Se imprime el valor de la media del anemómetro de los 3 segundos
    Serial.println(MediaAne3s);
    EnviarMediaAne3s = false; // Se desactiva la lectura de la media del anemómetro de los 3 segundos
    // ------------ Veleta ---------------
    Serial.print("Media veleta 3s: "); // Se imprime el valor de la media de la veleta de 3 segundos
    Serial.println(MediaVel3s);
    MediaVel3s = 0; // Se reinicia el valor acumulado de la media de la veleta de 3 segundos
    dt = clock.getDateTime();
    Serial.print(dt.year);Serial.print("-");Serial.print(dt.month);Serial.print("-");Serial.print(dt.day);Serial.print("/");
    Serial.print(dt.hour);Serial.print(":");Serial.print(dt.minute);Serial.print(":");Serial.println(dt.second);
  }
  if (EnviarMediaAne1min == true){ // Si se activa la lectura del BME280...
    Serial.print("Humidity:");Serial.print(mySensor.readFloatHumidity(), 0);Serial.print("/Pressure:");Serial.print(mySensor.readFloatPressure(), 0);
    Serial.print("/Alt:");Serial.print(mySensor.readFloatAltitudeMeters(), 1);Serial.print("/Temp:");Serial.println(mySensor.readTempC(), 2);
    // ------------ Reloj ---------------
    dt = clock.getDateTime();
    Serial.print(dt.year);Serial.print("-");Serial.print(dt.month);Serial.print("-");Serial.print(dt.day);Serial.print("/");
    Serial.print(dt.hour);Serial.print(":");Serial.print(dt.minute);Serial.print(":");Serial.println(dt.second);
    EnviarMediaAne1min = false;
  }
  if (EnviarMediaAne10min == true){ // Si se activa la lectura del anemómetro de los 10 minutos...
    // ------------ Anemómetro ---------------
    Serial.print("Media anemometro 10min: "); // Se imprime el valor de la media del anemómetro de los 10 minutos
    Serial.println(MediaAne10min);
    EnviarMediaAne10min = false; // Se desactiva la lectura de la media del anemómetro de los 10 minutos
    MediaAne10min = 0; // Se reinica el valor de la media del anemómetro de los 10 minutos
    // ------------ Veleta ---------------
    Serial.print("Media veleta 10 min: "); // Se imprime el valor de la media de la veleta de los 10 minutos
    Serial.println(MediaVel10min);
    MediaVel10min = 0; // Se reinicia la media de la veleta de 10 minutos
    // ------------ Reloj ---------------
    dt = clock.getDateTime();
    Serial.print(dt.year);Serial.print("-");Serial.print(dt.month);Serial.print("-");Serial.print(dt.day);Serial.print("/");
    Serial.print(dt.hour);Serial.print(":");Serial.print(dt.minute);Serial.print(":");Serial.println(dt.second);
  }
  if (EnviarMediaAne1h == true){ // Si se activa la lectura del anemómetro de 1 hora...
    // ------------ Anemómetro ---------------
    Serial.print("Media anemometro 1h: "); // Se imprime el valor de la media del anemómetro de 1 hora
    Serial.println(MediaAne1h);
    EnviarMediaAne1h = false; // Se desactiva la lectura de la media del anemómetro de 1 hora
    MediaAne1h = 0; // Se reinica el valor de la media del anemómetro de 1 hora
    // ------------ Veleta ---------------
    Serial.print("Media veleta 1 h: "); // Se imprime el valor de la media de la veleta de 1 hora
    Serial.println(MediaVel1h);
    MediaVel1h = 0; // Se reinica el valor de la media de la veleta de 1 hora
    // ------------ Pluviómetro ---------------
    Serial.print("Media pluviómetro 1 h: "); // Se imprime el valor de la media del pluviómetro de 1 hora
    Serial.println(MediaPlu1h);
    MediaPlu1h = 0; // Se reinica el valor de la media del pluviómetro de 1 hora
    // ------------ Reloj ---------------
    dt = clock.getDateTime();
    Serial.print(dt.year);Serial.print("-");Serial.print(dt.month);Serial.print("-");Serial.print(dt.day);Serial.print("/");
    Serial.print(dt.hour);Serial.print(":");Serial.print(dt.minute);Serial.print(":");Serial.println(dt.second);
  }
  if (EnviarMediaPlu3h == true){ // Si se activa la lectura de la media del pluviómetro de las 3 horas...
    // ------------ Pluviómetro ---------------
    Serial.print("Media pluviómetro 3 h: "); // Se imprime el valor de la media del poluviómetro de las 3 horas
    Serial.println(MediaPlu3h);
    EnviarMediaPlu3h == false; // Se desactiva la lectura de la media del pluviómetro de las 3 horas
    MediaPlu3h = 0; // Se reinicia el valor de la media del pluviómetro de las 3 horas
    // ------------ Reloj ---------------
    dt = clock.getDateTime();
    Serial.print(dt.year);Serial.print("-");Serial.print(dt.month);Serial.print("-");Serial.print(dt.day);Serial.print("/");
    Serial.print(dt.hour);Serial.print(":");Serial.print(dt.minute);Serial.print(":");Serial.println(dt.second);
  }
  if (EnviarMediaPlu1d == true){ // Si se activa la lectura de la media del pluviómetro de 1 día...
    // ------------ Pluviómetro ---------------
    Serial.print("Media pluviómetro 1 día: "); // Se imprime el valor de la media del pluviómetro de 1 día
    Serial.println(MediaPlu1d);
    EnviarMediaPlu1d == false; // Se desactiva la lectura de la media del pluviómetro de 1 día
    MediaPlu1d = 0; // Se reinicia la media del pluviómetro de 1 día
    // ------------ Reloj ---------------
    dt = clock.getDateTime();
    Serial.print(dt.year);Serial.print("-");Serial.print(dt.month);Serial.print("-");Serial.print(dt.day);Serial.print("/");
    Serial.print(dt.hour);Serial.print(":");Serial.print(dt.minute);Serial.print(":");Serial.println(dt.second);
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
  if ((a>=870)&&(a<=882)){
    return 0;
  }
  else if ((a>=45)&&(a<=48)){
    return 180;
  }
  else if ((a>=160)&&(a<=168)){
    return 270;
  }
  else if ((a>=630)&&(a<=640)){
    return 90;
  }
  else if ((a>=775)&&(a<=785)){
    return 45;
  }
  else if ((a>=447)&&(a<=456)){
    return 315;
  }
  else if ((a>=96)&&(a<=102)){
    return 225;
  }
  else if ((a>=288)&&(a<=298)){
    return 135;
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
