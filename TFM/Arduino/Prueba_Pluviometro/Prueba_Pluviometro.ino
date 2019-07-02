#include <math.h> 
#define PluvioPin (3)                 // Pin del Pluviómetro
volatile unsigned long Contactos;     // Contador nº de Contactos
volatile unsigned long DebounceTime;  // Temporizador para evitar el rebote del contacto 
float Lluvia;                         // Precipitaciones mm
float TimeMedia = 3000;               // Tiempo a realizar la media  
float Raincte  = 0.2794;              // mm x contacto

void setup() { 
  Serial.begin(9600); 
  pinMode(PluvioPin, INPUT); 
  attachInterrupt(digitalPinToInterrupt(PluvioPin), contact_count, FALLING); 
  Serial.println("Test de Pluviómetro"); 
  Serial.println("Contactos\tmm/s"); 
} 

void loop() { 
  Contactos = 0;      // Inicializar a 0 los contactos
  
  sei();              // Habilitar interrupciones 
  delay (TimeMedia);  // Espera del tiempo para hacer la media 
  cli();              // Deshabilitar interrupciones
  
  Lluvia = (Contactos * Raincte)/(TimeMedia/1000);
  
  Serial.print(Contactos); Serial.print("\t\t"); 
  Serial.println(Lluvia); 
} 

// Función que incrementa el número de contactos
void contact_count () {   
  if ((millis() - DebounceTime) > 30 ) { // Debounce con 30ms. 
  Contactos++; 
  DebounceTime = millis(); 
  } 
}
