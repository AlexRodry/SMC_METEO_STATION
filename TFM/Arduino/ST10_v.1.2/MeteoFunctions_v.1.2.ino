/*..................................................................................*/
/*...............................Funciones auxiliares...............................*/
/*..................................................................................*/
/*Declaracion de variables*/
//Contador
volatile int ms500Counter   = 0;        // Contador
volatile int maxCount = int(timeSeg*2); // Contador nº interrupciones
//Anemometro
volatile unsigned long Rots = 0;        // Contador nº de contactos anemómetro
volatile unsigned long DebAnemTime;     // Temporizador para evitar el rebote del contacto 
//Pluviometro
volatile unsigned long Pluvs = 0;       // Contador nº de Contactos
volatile unsigned long DebPluvTime;     // Temporizador para evitar el rebote del contacto 
//Veleta
int sensorValue;                        // Variable que almacena el valor raw (0 a 1023);
// Reloj
String dia;              // Variable temporal que almacena el día
String mes;              // Variable temporal que almacena el mes
String ano;              // Variable temporal que almacena el año
String hora;             // Variable temporal que almacena la hora
String minuto;           // Variable temporal que almacena los minutos
String segundo;          // Variable temporal que almacena los segundos
String _fecha;           // Variable temporal que almacena la cadena completa de la fecha

/* ----------------------------------- FUNCIONES ----------------------------------- */

// Función obtención de las medidas de los sensores
void ticks(){
  ms500Counter++;           // Contador del timer interno de Arduino
  /* Una vez que el contador llega al valor configurado inicialmente */
  if (ms500Counter == maxCount){
    /* Calculo de la velocidad del viento teniendo en cuenta
       el número de interrupciones que se han dado */
    sens[4] = String((Rots * Velcte)/(2*timeSeg));
    /* Calculo de la precipitación teniendo en cuenta
       el número de interrupciones que se han dado */
    sens[5] = String((Pluvs * Raincte)/(timeSeg));
    /* Calculo de la dirección del viento ejecutando la función
       que emplea los valores ya calibrados*/
    sens[3]  = direcc();
    ms500Counter = 0;     // Reseteo a 0 el contador de tiempo
    Rots = 0; Pluvs = 0;  // Reseteo a 0 los contadores de interrupciones
    readyToSend = true;   // Handshake para permitir el envío de datos   
  }
}

/* Función que incrementa el contador del anemómetro con interrupción */
void rot_count () { 
if ((millis() - DebAnemTime) > DFAnem ) { // Debounce con 75ms. 
  Rots++; 
  DebAnemTime = millis();
  } 
}
/* Función que incrementa el contador del pluviómetro con interrupción */
void pluv_count () { 
if ((millis() - DebPluvTime) > DFpluv ) { // Debounce con 75ms. 
  Pluvs++; 
  DebPluvTime = millis();
  } 
}

/* Función obtención de la dirección del viento en f(Resistencia) */
String direcc()
{
  int a = analogRead(VelPin);   // Lectura tensión de entrada
  /* Obtención de la dirección del viento tras la correcta
     calibración y configuración */
  if ((a>=Nort[0])&&(a<=Nort[1])){
    return "0";
  }
  else if ((a>=NortO[0])&&(a<=NortO[1])){
    return "45";
  }
  else if ((a>=Sur[0])&&(a<=Sur[1])){
    return "180";
  }
  else if ((a>=SurO[0])&&(a<=SurO[1])){
    return "135";
  }
  else if (a>=Este[0]){
    return "90";
  }
  else if ((a>=SurE[0])&&(a<=SurE[1])){
    return "225";
  }
  else if (a<=Oest[0]){
    return "270";
  }
  else if ((a>=NortE[0])&&(a<=NortE[1])){
    return "315";
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
