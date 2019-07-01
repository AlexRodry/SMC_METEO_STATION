
const int sensorPin = A1; // seleccionar la entrada para el sensor
int sensorValue;          // Variable que almacena el valor raw (0 a 1023)
String veleta;            // Dirección que marca la veleta 
void setup()
{
   Serial.begin(9600);
   Serial.println("Test de Veleta"); 
   Serial.println("Raw Value\tDirección"); 
}
 
void loop() 
{
   sensorValue = analogRead(sensorPin);       // Realiza la lectura
   veleta = direction(sensorValue);           // Se procesa el valor Raw con una función
   delay(1000);
   Serial.print(sensorValue); Serial.print("\t\t"); Serial.println(veleta); 
}

String direction(int a)
{
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
