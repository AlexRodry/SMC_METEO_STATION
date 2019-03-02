void setup() {
  Serial.begin(9600);
}

void loop() {
  float v = anemometro();
  String cad = String(v) + " km/h"; 
  Serial.println(cad);
}

/* 
 * La función anemómetro mide la velocidad del viento en km/h. Para ello se debe definir previamente
 * el pin analógico al que se conectará el anemómetro en la placa de Aurduino. La función devuelve 
 * un valor de velocidad de tipo float.
 */
int pinAne = 7; // Pin analógico al que se conectará el anemómetro
float anemometro(){
  unsigned long comienzo_anemometro = millis(); // Inicio contador de tiempo
  int vueltas = 0; // Se inicializa una variable que cuente las vueltas
  int estado1; // Se inicializa una variable de estado
  // Se usa un bucle para que la función se ejecute durante un tiempo determinado (5 segundos)
  while (abs(millis() - comienzo_anemometro) <= 5000){
    /* Para poder detectar cada vuelta se simula un biestable en el que se crea un estado que corresponde con
       estar bien cercano al interruptor magnético o bien alejado, es decir, poder contar una vuelta o no
    */
    if(analogRead(pinAne) >= 1020){
      estado1 = 0;
      delay(10);
    }
    else{
      estado1 = 1;
      delay(10);
    }
    // Las vueltas se contarán cuando se parta de un estado de lejanía al interruptor y se llegue a un valor de 
    if((analogRead(pinAne) < 1020)&&(estado1 == 0)){
      vueltas++; // Se incrementa el número de vueltas de uno en uno
      /* Para poder registrar vientos de hasta 48 km/h se deben poder captar hasta 20 vueltas por segundo
       por lo que se deberá contar cada 50 milisegundos como mucho */
      delay(50);
    }
  }
  unsigned long fin_anemometro = millis(); // Contador de final de tiempo
  unsigned long tiempo = (fin_anemometro - comienzo_anemometro)/1000; // Tiempo en el que la función está midiendo en segundos
  //Serial.println(tiempo); // Comprobación de que la función mide durante 5 segundos
  //Serial.println(vueltas); // Comprobación de que la función cuenta las vueltas
  // Una vuelta por segundo corresponde a 2.4 km/h
  float tiempofloat = (float)tiempo; // Paso del tiempo de tipo unsigned long a float
  float velocidad_unitaria = (vueltas/2)/tiempofloat; // Cálculo de vueltas por segundo que se han dado en los 5 segundos de medida
  //Serial.println(velocidad_unitaria); // Comprobación de que se está calculando bien la velocidad unitaria
  float velocidad = 2.4*velocidad_unitaria; // Cáculo de la velocidad del viento
  //Serial.println(velocidad); // Comprobación de que se está calculando bien la velocidad
  return velocidad; // Se devuelve el valor de velocidad calculado por la función
}
