/*Librerías*/
#include <math.h>     // Calculos

/*Declaracion de variables*/

//Anemometro
volatile unsigned long Rots;          // Contador nº de giros
volatile unsigned long DebAnemTime;   // Temporizador para evitar el rebote del contacto 

//float Velo;                         // Velocidad km/h 
float TimeMediaAnem = 3000;           // Tiempo a realizar la media  
float Velcte  = 2.4;                  // km/h x rev

//Pluviometro
volatile unsigned long Pluvs;         // Contador nº de Contactos
volatile unsigned long DebPluvTime;   // Temporizador para evitar el rebote del contacto 
float Raincte  = 0.2794;              // mm x contacto

//Veleta
int sensorValue;                      // Variable que almacena el valor raw (0 a 1023);

// Reloj
int dia;
int mes;
int ano;
int hora;
int minuto;
int segundo;
char buff[14];
String _fecha;

/*----- ANEMOMETRO -----*/
// Función obtención de la velocidad del anemometro
void ticks(){
  Rots = 0; Pluvs = 0;      // Inicializar a 0 las vuelta
  //sei();                  // Habilitar interrupciones 
  delay (TimeMediaAnem);    // Espera del tiempo para hacer la media
  //cli();                  // Deshabilitar interrupciones
  velo   = String((Rots * Velcte)/(TimeMediaAnem*0.001));
  pluvio = String((Pluvs * Raincte)/(TimeMediaAnem/1000));
}
// Función que incrementa el número de rotaciones con interrupción
void rot_count () { 
if ((millis() - DebAnemTime) > 15 ) { // Debounce con 15ms. 
  Rots++; 
  DebAnemTime = millis();
  } 
}
void pluv_count () { 
if ((millis() - DebPluvTime) > 15 ) { // Debounce con 15ms. 
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
   mes = now.month();
   ano = now.year();
   hora = now.hour();
   minuto = now.minute();
   segundo = now.second();
   
   sprintf(buff, "%04d%02d%02d%02d%02d%02d", ano, mes, dia, hora, minuto, segundo);
   _fecha = String(buff);
   buff[14] = "";
   return _fecha;
}
