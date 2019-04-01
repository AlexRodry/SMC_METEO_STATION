#include <TimerOne.h>

volatile int CuentaAne = 0;
volatile int CuentaAne250ms = 0;
volatile int CuentaAne3s = 0;
volatile int CuentaAne1min = 0;
volatile int CuentaAne10min = 0;
float rev3s;
float MediaAne3s;
float MediaAne10min = 0;
float MediaAne1h = 0;
boolean EnviarMediaAne3s = false;
boolean EnviarMediaAne10min = false;
boolean EnviarMediaAne1h = false;

boolean EnviarMediaVel1min = false;
boolean EnviarMediaVel10min = false;
int MediaVel3s;
int MediaVel1min = 0;
float MediaVel10min;

void setup() {
  Serial.begin(9600);
  Timer1.initialize(250000); // Salta el timer 1 cada 250 ms
  Timer1.attachInterrupt(tiempo_ane); // Salta la función tiempo_ane a la frecuencia indicada antes
  attachInterrupt(0, Ane, RISING); // Asigna la interrupción 0 (pin D2) a la función Ane cuando detecta un flanco de subida
}

void loop() {
  if (EnviarMediaAne3s == true){ // Si se activa la lectura de la media del anemómetro de 3 segundos...
    // ------------ Anemómetro ---------------
    Serial.print("Media anemometro 3s: "); // Se imprime el valor de la media del anemómetro de los 3 segundos
    Serial.println(MediaAne3s);
    EnviarMediaAne3s = false; // Se desactiva la lectura de la media del anemómetro de los 3 segundos
    // ------------ Veleta ---------------
    Serial.print("Media veleta 3s: "); // Se imprime el valor de la media de la veleta de 1 minuto
    Serial.println(MediaVel3s);
    MediaVel3s = 0; // Se reinicia el valor acumulado de la media de la veleta de 1 minuto
  }
  if (EnviarMediaAne10min == true){ // Si se activa la lectura del anemómetro de los 10 minutos...
    // ------------ Anemómetro ---------------
    Serial.print("Media anemometro 10min: "); // Se imprime el valor de la media del anemómetro de los 10 minutos
    Serial.println(MediaAne10min);
    EnviarMediaAne10min = false; // Se desactiva la lectura de la media del anemómetro de los 10 minutos
    MediaAne10min = 0; // Se reinica el valor de la media del anemómetro de los 10 minutos
    // ------------ Veleta ---------------
    Serial.print("Media veleta 10 min: ");
    Serial.println(MediaVel10min);
    MediaVel10min = 0;
  }
  if (EnviarMediaAne1h == true){ // Si se activa la lectura del anemómetro de 1 hora...
    // ------------ Anemómetro ---------------
    Serial.print("Media anemometro 1h: "); // Se imprime el valor de la media del anemómetro de 1 hora
    Serial.println(MediaAne1h);
    EnviarMediaAne1h = false; // Se desactiva la lectura de la media del anemómetro de 1 hora
    MediaAne1h = 0; // Se reinica el valor de la media del anemómetro de 1 hora
    // ------------ Veleta ---------------
    Serial.print("Media veleta 1 h: ");
    Serial.println(MediaVel1h);
    MediaVel1h = 0;
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
    MediaAne10min = MediaAne10min + MediaAne3s; // Se acumula el valor de las medias de 3 segundos para hacer una media de los 10 minutos
    CuentaAne250ms = 0; // La cuenta de 250 milisegundos se reinicia
    CuentaAne = 0; // Se reinicia la cuenta de vueltas del anemómetro
    // ------------ Veleta ---------------
    MediaVel3s = veleta(); // Se lee la veleta y se devuelve el valor de los grados respecto al norte
    MediaVel10min = MediaVel3s + MediaVel10min; // Se acumulan los valores de los grados para hacer la media de la veleta en 10 minutos
  }
  if (CuentaAne3s == 20){ // Cuando la cuenta del anemómetro llegue a 20, es decir, 1 minuto...
    // ------------ Anemómetro ---------------
    CuentaAne1min++; // Se incrementa el contador del anemómetro de 1 minuto
    CuentaAne3s = 0; // Se reinicia el contador del anemómetro de 3 segundos
    // ------------ BME280 ---------------
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
    MediaAne1h = MediaAne1h/6; // Se hace la media de los 6 valores acumulados de la media de 10 minutos
    EnviarMediaAne1h = true; // Se activa la lectura de la media de la hora
    CuentaAne10min = 0; // Se reinicia la cuenta de los 10 minutos
    // ------------ Veleta ---------------
    MediaVel1h = MediaVel1h/6; // Se hace la media de los 6 datos de la media de 10 minutos acumulados de la veleta
  }
}

void Ane(){
  CuentaAne++; // Se incrementa el número de pulsos detectados
}

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
