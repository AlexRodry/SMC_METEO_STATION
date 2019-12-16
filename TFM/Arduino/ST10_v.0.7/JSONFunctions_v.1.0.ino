/*Librerias*/
#include <ArduinoJson.h>

void json_telegram(){

  StaticJsonBuffer<4500> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  
  json["nombre"] = "ST10";
  
  JsonObject& s1 = jsonBuffer.createObject();// Fecha del dato
  
  s1["Fecha"] = String(fecha);
  
  JsonObject& st = jsonBuffer.createObject(); // Tipo dato
  
  st["Tipo"] = "6"; //Json con 6 datos
  
  JsonArray& datosS1 = json.createNestedArray("Dato");
  
  datosS1.add(s1);
  datosS1.add(st);
  
  JsonObject& s3 = jsonBuffer.createObject(); // Humedad
  s3["id"] = "1";
  s3["valor"] = String(hum);
  
  JsonObject& s4 = jsonBuffer.createObject(); // Presion
  s4["id"] = "2";
  s4["valor"] = String(pres);
  
  JsonObject& s5 = jsonBuffer.createObject(); // Temperatura
  s5["id"] = "3";
  s5["valor"] = String(temp);
  
  JsonObject& s6 = jsonBuffer.createObject(); // Direccion
  s6["id"] = "4";
  s6["valor"] = String(veleta);
  
  JsonObject& s7 = jsonBuffer.createObject(); // Velocidad
  s7["id"] = "5";
  s7["valor"] = String(velo);
  
  JsonObject& s8 = jsonBuffer.createObject(); // Lluvia
  s8["id"] = "6";
  s8["valor"] = String(pluvio);
  
  JsonArray& datosS = json.createNestedArray("sensores");
  datosS.add(s3);
  datosS.add(s4);
  datosS.add(s5);
  datosS.add(s6);
  datosS.add(s7);
  datosS.add(s8);
  json.printTo(Serial);
  delay(50);
  Serial.println();
}
