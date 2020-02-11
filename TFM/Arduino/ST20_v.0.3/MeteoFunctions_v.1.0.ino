/*.......................................................................*/
/*.........................Funciones auxiliares..........................*/
/*.......................................................................*/
/*Declaracion de variables*/
//Contador
volatile int ms500Counter = 0;          // Contador
volatile int maxCount = int(timeSeg*2); // Contador nº interrupciones
// Reloj
String dia;              // Variable temporal que almacena el día
String mes;              // Variable temporal que almacena el mes
String ano;              // Variable temporal que almacena el año
String hora;             // Variable temporal que almacena la hora
String minuto;           // Variable temporal que almacena los minutos
String segundo;          // Variable temporal que almacena los segundos
String _fecha;           // Variable temporal que almacena la cadena completa de la fecha

/* -------------------------- FUNCIONES ----------------------------- */

// Función obtención de las medidas de los sensores
// Función obtención de la temperatura
void ticks(){  
  ms500Counter++;
  /* Una vez que el contador llega al valor configurado inicialmente */
  if (ms500Counter == maxCount){    
    // Con analogRead leemos el sensor, recuerda que es un valor de 0 a 1023  // Todelete
    tempC = analogRead(pinLM35);                                              // Todelete   
    // Calculamos la temperatura con la fórmula                               // Todelete
    sens[2] = String((tempC * 110.0)/1024.0);                                 // Todelete
    ms500Counter = 0;         // Reseteo a 0 el contador de tiempo
    readyToSend = true;       // Handshake para permitir el envío de datos
  }
}

/* Función obtención de la fecha con formato sin separación */
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
  /* Concatenación en la variable temporal de fecha */
  _fecha = ano + mes + dia + hora + minuto + segundo;
   return _fecha;
}
