//--Interrupciones reloj
#include <TimerOne.h>

// Declaracion de variables temperatura
volatile float tempC; // Variable para almacenar el valor obtenido del sensor (0 a 1023)
int pinLM35 = 3; // Variable del pin de entrada del sensor (A0)

// Declaracion de variables de fecha constante
String fecha = "20200111210000";

String ids[] = {"11", "20"};
String sens[] = {"temp","rssi"};
int nids = 7;

String SerialTelegram;
String Sep = "|";
String St = "ST02";

// Handshake de envio
volatile bool readyToSend = false;

void setup() {
  // Configuramos el puerto serial a 9600 bps
  Serial.begin(9600);
  analogReference(INTERNAL);
  Timer1.initialize(500000);          // Activación del timer 1 cada 500ms
  Timer1.attachInterrupt(counter);      // Salta la función leer temperatura
}
 
void loop() {    
 if (readyToSend == true){
    delay(50);
    SerialTelegram = "Nombre"+Sep+St+Sep+ "Fecha"+Sep+fecha+Sep +ids[0]+Sep+sens[0]+Sep +ids[1]+Sep+sens[1]+Sep;
    Serial.println(SerialTelegram);
    readyToSend = false;
  }
}
