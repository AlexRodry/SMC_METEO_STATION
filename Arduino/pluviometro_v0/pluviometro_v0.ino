int pinPlu = 11; // Pin analógico al que va conectado el pluviómetro

void setup() {
  Serial.begin(9600);
  pinMode(pinPlu, INPUT); // Asigno el pin del pluviómetro como un pin de entrada
}

void loop() {
  float plu = pluviometro(); // Uso la función pluviometro para medir la cantidad de lluvia
  String cad = String(plu) + " mm"; // Creo una cadena para que me de el resultado con sus unidades
  Serial.println(cad); // Saco por el puerto serie la cadena
}
/*  
 * La función pluviometro() es una función que devuelve el valor de lluvia en mm en tipo float.
 * Se necesita indicar el pin analógico al que va conectado el pluviómetro.
 */
float pluviometro(){
  unsigned long tiempo1 = millis(); // Se inicia un contador para ller datos durante un tiempo determinado
  float cuenta = 0; // Se inicia la cuenta de giros del pluviómetro
  int entrada; // Se inicializa la variable de lectura del pluviómetro
  while(abs(millis() - tiempo1)< 5000){ // Se crea un bucle para que la función lea durante el tiempo de lectura
    entrada = analogRead(pinPlu); // Se lee el anemómetro
    if (entrada == 1023){ // Si se detecta una subida...
      delay(50); // ... Espero 50 milis...
      if(analogRead(pinPlu) == 1023){ // ... y vuelvo a comprobar si sigo en la subida
        cuenta = cuenta + 1; // Como se sigue en la subida se cuenta 1 giro
        delay(100); // Se espera para que de tiempo a bajar a "entrada"
      }
    }
    //Serial.println(cuenta); // Comprobación de la cuenta de giros instantánea
    //Serial.println(entrada); // Comprobación de la entrada
  }
  //Serial.println(cuenta); // Comprobación de la cuenta de giros
  float lluvia = cuenta*0.2794; // 0.2794 mm por pulso
  return lluvia; // Se saca el valor de la lluvia
}
