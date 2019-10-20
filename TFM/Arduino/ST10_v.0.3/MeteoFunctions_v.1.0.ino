/*Librerías*/
#include <math.h>     // Calculos

/*Declaración de Inputs/Outputs*/
//#define AnemPin (2)                   // Pin del Anemómetro

/*Declaracion de variables*/
volatile unsigned long Rots;          // Contador nº de giros
volatile unsigned long DebAnemTime;   // Temporizador para evitar el rebote del contacto 
float Velo;                           // Velocidad km/h 
float TimeMediaAnem = 3000;           // Tiempo a realizar la media  
float Velcte  = 2.4;                  // km/h x rev

/*----- ANEMOMETRO -----*/
// Función obtención de la velocidad del anemometro
String anem(){
  String _velo;
  Rots = 0;               // Inicializar a 0 las vuelta
  sei();                  // Habilitar interrupciones 
  delay (TimeMediaAnem);  // Espera del tiempo para hacer la media
  valor = random(0,2);
  if (valor == 1){
    digitalWrite(pinAnemInt,HIGH);
  }
  else{
    digitalWrite(pinAnemInt,LOW);
  }
  Serial.println(digitalRead(2)); 
  cli();                  // Deshabilitar interrupcione
  _velo = String((Rots * Velcte)/(TimeMediaAnem*0.001));
  return _velo;
}
// Función que incrementa el número de rotaciones con interrupción
void rot_count () { 
if ((millis() - DebAnemTime) > 15 ) { // Debounce con 15ms. 
  Rots++; 
  DebAnemTime = millis(); 
  } 
}
