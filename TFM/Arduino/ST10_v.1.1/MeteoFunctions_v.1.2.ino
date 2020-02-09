/*Librerías*/
#include <math.h>     // Calculos

/*Declaracion de variables*/
// Contador
volatile int ms500Counter   = 0;                // Contador
volatile float timeSeg      = 10;                // Tiempo en segundos de envío
volatile int maxCount       = int(timeSeg*2);   // Contador nº interrupciones
//Anemometro
volatile unsigned long Rots = 0;        // Contador nº de giros
volatile unsigned long DebAnemTime;     // Temporizador para evitar el rebote del contacto 

//float Velo;                           // Velocidad km/h 
float TimeMediaAnem = 3000;             // Tiempo a realizar la media  
float Velcte  = 2.4;                    // km/h x rev

//Pluviometro
volatile unsigned long Pluvs = 0;       // Contador nº de Contactos
volatile unsigned long DebPluvTime;     // Temporizador para evitar el rebote del contacto 
float Raincte  = 0.2794;                // mm x contacto

//Veleta
int sensorValue;                        // Variable que almacena el valor raw (0 a 1023);

// Reloj
String dia;
String mes;
String ano;
String hora;
String minuto;
String segundo;
String _fecha;

/*----- ANEMOMETRO -----*/
// Función obtención de la velocidad del anemometro
void ticks(){
  ms500Counter++;
  if (ms500Counter == maxCount){
    sens[4] = String((Rots * Velcte)/(2*timeSeg));
    sens[5] = String((Pluvs * Raincte)/(timeSeg));
    ms500Counter = 0;
    sens[3]  = direcc();
    readyToSend = true;
    Rots = 0; Pluvs = 0;      // Inicializar a 0 las vuelta
  }
}
// Función que incrementa el número de rotaciones con interrupción
void rot_count () { 
if ((millis() - DebAnemTime) > 75 ) { // Debounce con 75ms. 
  Rots++; 
  DebAnemTime = millis();
  } 
}
void pluv_count () { 
if ((millis() - DebPluvTime) > 75 ) { // Debounce con 75ms. 
  Pluvs++; 
  DebPluvTime = millis();
  } 
}
/*----- VELETA -----*/
// Función obtención de la dirección en f(R)
String direcc()
{
  sensorValue = analogRead(VelPin);
  int a = sensorValue;
  if ((a>=225)&&(a<=400)){
    return "0";
  }
  else if ((a>=501)&&(a<=675)){
    return "45";
  }
  else if ((a>=676)&&(a<=800)){
    return "180";
  }
  else if ((a>=801)&&(a<=895)){
    return "135";
  }
  else if (a>=895){
    return "90";
  }
  else if ((a>=401)&&(a<=500)){
    return "225";
  }
  else if (a<=140){
    return "270";
  }
  else if ((a>=141)&&(a<=224)){
    return "315";
  }
}
/*----- RELOJ -----*/
String funFecha(){
  
  DateTime now = rtc.now();
  dia = now.day();
  if (dia.length() < 2){
    dia = "0" + dia;
  }
  mes = now.month();
  if (mes.length() < 2){
    mes = "0" + mes;
  }
  ano = now.year();
  hora = now.hour();
  if (hora.length() < 2){
    hora = "0" + hora;
  }
  minuto = now.minute();
  if (minuto.length() < 2){
    minuto = "0" + minuto;
  }
  segundo = now.second(); 
  if (segundo.length() < 2){
    segundo = "0" + segundo;
  }
  _fecha = ano + mes + dia + hora + minuto + segundo;
   return _fecha;
}
