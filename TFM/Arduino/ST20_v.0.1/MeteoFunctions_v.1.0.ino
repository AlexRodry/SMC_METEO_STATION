/*Librerías*/
#include <math.h>     // Calculos
/*Declaracion de variables*/
// Contador
volatile int ms500Counter   = 0;                // Contador
volatile float timeSeg      = 10;               // Tiempo en segundos de envío
volatile int maxCount       = int(timeSeg*2);   // Contador nº interrupciones

/*----- ANEMOMETRO -----*/
// Función obtención de la temperatura
void tempRead(){  
  ms500Counter++;
  if (ms500Counter == maxCount){
    // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023
    tempC = analogRead(pinLM35);   
    // Calculamos la temperatura con la fórmula
    tempC = (tempC * 110.0)/1024.0; 
    ms500Counter = 0;
    readyToSend = true;
  }
}
