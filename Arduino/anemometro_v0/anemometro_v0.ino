#include <TimerOne.h>

volatile int CuentaAne = 0;
volatile int CuentaAne250ms = 0;
volatile int CuentaAne3s = 0;
volatile int CuentaAne10min = 0;
float rev3s;
float Media3s;
float Media10min = 0;
float Media1h = 0;
boolean EnviarMedia3s = false;
boolean EnviarMedia10min = false;
boolean EnviarMedia1h = false;

void setup() {
  Serial.begin(9600);
  Timer1.initialize(250000); // Salta el timer 1 cada 250 ms
  Timer1.attachInterrupt(tiempo_ane); // Salta la función tiempo_ane a la frecuencia indicada antes
  attachInterrupt(0, Ane, RISING); // Asigna la interrupción 0 (pin D2) a la función Ane cuando detecta un flanco de subida
}

void loop() {
  
  //Serial.println(CuentaAne250ms);
  //Serial.println(CuentaAne3s);
  //Serial.println(CuentaAne10min);
  //Serial.println(CuentaAne);
  //Serial.println(media3s);
  if (EnviarMedia3s == true){ // Si se activa la lectura de la media de 3 segundos...
    Serial.print("Media 3s: "); // Se imprime el valor de la media de los 3 segundos
    Serial.println(Media3s);
    EnviarMedia3s = false; // Se desactiva la lectura de la media de los 3 segundos
  }
  if (EnviarMedia10min == true){ // Si se activa la lectura de los 10 minutos...
    Serial.print("Media 10min: "); // Se imprime el valor de la media de los 10 minutos
    Serial.println(Media10min);
    EnviarMedia10min = false; // Se desactiva la lectura de la media de los 10 minutos
    Media10min = 0; // Se reinica el valor de la media de los 10 minutos
  }
  if (EnviarMedia1h == true){ // Si se activa la lectura de la hora...
    Serial.print("Media 1h: "); // Se imprime el valor de la media de la hora
    Serial.println(Media1h);
    EnviarMedia1h = false; // Se desactiva la lectura de la media de la hora
    Media1h = 0; // Se reinica el valor de la media de la hora
  }
}

void tiempo_ane(){
  CuentaAne250ms++; // Se incrementa la variable cuendo se activa la función, es decir, cada 250 milisegundos
  if (CuentaAne250ms == 12){ // Cuando el timer alcanza 12 pulsos (3 segundos)...
    CuentaAne3s++; // Se aumenta el contador de 3 segundos
    CuentaAne250ms = 0; // La cuenta de 250 milisegundos se reinicia
    rev3s = ((float)CuentaAne)/(2*3); // Se calcula el número de revoluciones por segundo que se han medido en los 3 segundos (teniendo en cuenta que hay dos pulsos por vuelta)
    Media3s = 2.4*rev3s; // Se realiza la equivalencia de revoluciones por segundo a kilómetros por hora. 1 revolución por segundo corresponde a 2.4 km/h
    EnviarMedia3s = true; // Se activa la lectura de la media de los 3 segundos
    Media10min = Media10min + Media3s; // Se acumula el valor de las medias de 3 segundos para hacer una media de los 10 minutos
    CuentaAne = 0; // Se reinicia la cuenta de vueltas del anemómetro
  }
  if (CuentaAne3s == 200){ // Cuando la cuenta de los 3 segundos llega a 200, es decir, a 10 minutos...
    CuentaAne10min++; // Se incrementa el contador de los 10 minutos
    Media10min = Media10min/200; // Se hace la media de los 200 valores acumulados de la media de 3 segundos
    Media1h = Media1h + Media10min; // Se acumula el valor medio de cada 10 minutos para calcular la media de la hora
    EnviarMedia10min = true; // Se activa la lectura de la media de los 10 minutos
    CuentaAne3s = 0; // Se reinicia la cuenta de los 3 segundos
  }
  if (CuentaAne10min == 6){ // Cuando la cuenta de los 10 minutos ha llegado a 6, es decir, a 1 hora...
    Media1h = Media1h/6; // Se hace la media de los 6 valores acumulados de la media de 10 minutos
    EnviarMedia1h = true; // Se activa la lectura de la media de la hora
    CuentaAne10min = 0; // Se reinicia la cuenta de los 10 minutos
  }
}

void Ane(){
  CuentaAne++; // Se incrementa el número de pulsos detectados
}
