#include <math.h> 

#define AnemPin (2) // The pin location of the anemometer sensor 

volatile unsigned long Rots;         // Contador nº de giros
volatile unsigned long DebounceTime; // Temporizador para evitar el rebote del contacto 

float Velo;                // Velcidad km/h 
float TimeMedia = 1000;    // Tiempo a realizar la media  
float Velcte  = 2.4;       // km/h x rev

void setup() { 
Serial.begin(9600); 

pinMode(AnemPin, INPUT); 
attachInterrupt(digitalPinToInterrupt(AnemPin), isr_rotation, FALLING); 

Serial.println("Test de Anemómetro"); 
Serial.println("Giros\tkm/h"); 
} 

void loop() { 

Rots = 0;           // Inicializar a 0 las vueltas

sei();              // Habilitar interrupciones 
delay (TimeMedia);  // Espera del tiempo para hacer la media 
cli();              // Deshabilitar interrupciones 

// convert to mp/h using the formula V=P(2.25/T) 
// V = P(2.25/3) = P * 0.75 

Velo = Rots * Velcte; 

Serial.print(Rots); Serial.print("\t\t"); 
Serial.println(Velo); 

} 

// Función que incrementa el número de rotaciones
void isr_rotation () { 

if ((millis() - DebounceTime) > 15 ) { // debounce the switch contact. 
Rots++; 
DebounceTime = millis(); 
} 

}
