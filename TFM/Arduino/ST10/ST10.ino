/*---------------LIBRERIAS-------------*/

#include <math.h>           // Librería para cálculos
#include "SparkFunBME280.h" // Librería del sensor
#include <RTClib.h>         
#include <Wire.h>           // Comunicación I2C

/*--------------VARIABLES--------------*/

// Variables para el BME280
BME280 mySensor;
float hum;                            // Humedad en %HR
float pres;                           // Presión en Pa
float temp;                           // Temperatura en ºC

// Variables para el anemómetro
#define AnemPin (2)                   // Pin del Anemómetro
volatile unsigned long Rots;          // Contador nº de giros
volatile unsigned long DebounceAnem;  // Temporizador para evitar el rebote del contacto 
float Velo;                           // Velocidad km/h 
float TimeAnem = 3000;                // Tiempo a realizar la media ms
float Velcte  = 2.4;                  // km/h x rev

// Variables para el pluviómetro
#define PluvioPin (3)                 // Pin del Pluviómetro
volatile unsigned long Contactos;     // Contador nº de Contactos
volatile unsigned long DebouncePluv;  // Temporizador para evitar el rebote del contacto 
float Lluvia;                         // Precipitaciones mm
float TimePluv = 3000;                // Tiempo a realizar la media ms
float Raincte  = 0.2794;              // mm x contacto

// Variables de la veleta
const int sensorPin = A1;             // seleccionar la entrada para el sensor
int sensorValue;                      // Variable que almacena el valor raw (0 a 1023)
String veleta;                        // Dirección que marca la veleta 

// Variables del reloj
RTC_DS3231 rtc;                       // Declaramos un RTC DS3231
String fecha; 

/*------------CONFIGURACIÓN------------*/

void setup() { 
  Serial.begin(115200);   // Velocidad de transmisión con pycom
  Serial.println("Iniciando...");
  // Interrupciones para el Anemómetro
  pinMode(AnemPin, INPUT); 
  attachInterrupt(digitalPinToInterrupt(AnemPin), rot_count, FALLING); 
  // Interrupciones para el Pluviómetro
  pinMode(PluvioPin, INPUT); 
  attachInterrupt(digitalPinToInterrupt(PluvioPin), contact_count, FALLING);
  // Comprobación de la conexión con el módulo RTC
  if (! rtc.begin()) {
    Serial.println("No hay conexión con el módulo RTC");
    while (1); //Freeze
    }
  // Comprobación de la conexión con el módulo BME280
  if (mySensor.beginI2C() == false) {
    Serial.println("No hay conexión con el módulo BME280");
    while(1); //Freeze
    }
  // Setear la hora del reloj a la hora que se ha cargado el SW
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("Listo");
} 

/*---------PROGRAMA PRINCIPAL---------*/

void loop() { 

  // Cálculo humedad, presión y temperatura
  hum   = mySensor.readFloatHumidity();
  pres  = mySensor.readFloatPressure();
  temp  = mySensor.readTempC();
  Serial.println("1");

  // Fecha
  Serial.println("2");
  fecha = reloj();

  Serial.println(fecha);
  Serial.println("3");

  // Cálculo dirección del viento
  sensorValue = analogRead(sensorPin); // Realiza la lectura
  Serial.println("4.1");
  veleta = direction(sensorValue);     // Se procesa el valor Raw con una función
  Serial.println("4.2");
 
  // Cálculo velocidad del viento
  Rots = 0;                             // Inicializar a 0 las vuelta
  sei();                                // Habilitar interrupciones 
  delay (TimeAnem);                     // Espera del tiempo para hacer la media 
  cli();                                // Deshabilitar interrupciones
  Velo = (Rots * Velcte)/(TimeAnem*0.001);
  Serial.println("5");

  // Cálculo lluvia
  Contactos = 0;                        // Inicializar a 0 los contactos 
  sei();                                // Habilitar interrupciones 
  delay (TimePluv);                     // Espera del tiempo para hacer la media 
  cli();                                // Deshabilitar interrupciones  
  Lluvia = (Contactos * Raincte)/(TimePluv/1000);
  Serial.println("6");

} 

/*--------FUNCIONES SECUNDARIAS-------*/

/*ANEMÓMETRO*/

// Función que incrementa el número de rotaciones
void rot_count () { 
  if ((millis() - DebounceAnem) > 15 ) { // Debounce con 15ms. 
    Rots++; 
    DebounceAnem = millis(); 
  } 
}

/*PLUVIÓMETRO*/

// Función que incrementa el número de contactos
void contact_count () {   
  if ((millis() - DebouncePluv) > 30 ) { // Debounce con 30ms. 
  Contactos++; 
  DebouncePluv = millis(); 
  } 
}

/*VELETA*/

String direction(int a){
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

/*RELOJ*/

String reloj (){
  DateTime now = rtc.now();
  String date;
  date = (String(now.day(),DEC) + '/' + 
          String(now.month(),DEC) + '/' + 
          String(now.year(),DEC) + ' ' + 
          String(now.hour(),DEC) + ':' +
          String(now.minute(),DEC) + ':' + 
          String(now.second(),DEC));
  return date;
}
