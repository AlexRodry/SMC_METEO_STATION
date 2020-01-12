/*Librerias*/
#include <ArduinoJson.h>

void json_telegram(){

  StaticJsonBuffer<4500> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  
  json["nombre"] = "ST20";
  
  JsonObject& s1 = jsonBuffer.createObject();// Fecha del dato
  
  s1["Fecha"] = String(fecha);
  
  JsonObject& st = jsonBuffer.createObject(); // Tipo dato
  
  st["Tipo"] = "1"; //Json con 1 dato
  
  JsonArray& datosS1 = json.createNestedArray("Dato");
  
  datosS1.add(s1);
  datosS1.add(st);
  
  JsonObject& s3 = jsonBuffer.createObject(); // Temperatura
  s3["id"] = "7";
  s3["valor"] = String(tempC);
  
  JsonArray& datosS = json.createNestedArray("sensores");
  datosS.add(s3);

  json.printTo(Serial);
  delay(50);
  Serial.println();
}
