#include <math.h> 
#define AnemPin (2)                   // Pin del Anemómetro
volatile unsigned long Rots;          // Contador nº de giros
volatile unsigned long DebounceTime;  // Temporizador para evitar el rebote del contacto 
float Velo;                           // Velocidad km/h 
float TimeMedia = 3000;               // Tiempo a realizar la media  
float Velcte  = 2.4;                  // km/h x rev

void setup() { 
Serial.begin(9600); 
pinMode(AnemPin, INPUT); 
attachInterrupt(digitalPinToInterrupt(AnemPin), rot_count, RISING); 
Serial.println("Test de Anemómetro"); 
Serial.println("Giros\tkm/h"); 
} 

void loop() { 
Rots = 0;           // Inicializar a 0 las vuelta

sei();              // Habilitar interrupciones 
delay (TimeMedia);  // Espera del tiempo para hacer la media 
cli();              // Deshabilitar interrupcione

Velo = (Rots * Velcte)/(TimeMedia*0.001);

Serial.print(Rots); Serial.print("\t\t"); 
Serial.println(Velo); 
} 

// Función que incrementa el número de rotaciones
void rot_count () { 

if ((millis() - DebounceTime) > 15 ) { // Debounce con 15ms. 
Rots++; 
DebounceTime = millis(); 
} 

}
