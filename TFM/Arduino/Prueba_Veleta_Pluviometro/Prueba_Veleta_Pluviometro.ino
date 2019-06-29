
int velet;  // Grados donde marca la veleta
bool anem;

void setup() {
  Serial.begin(9600);

}

void loop() {
  //velet = veleta();
  //velet = analogRead(A1);
  anem = digitalRead(2);
  //Serial.println(velet + " º");
  //delay (500);
  Serial.println(anem);
  delay (500);
}

int veleta(){
  int a = analogRead(1);
  if ((a>=850)&&(a<=900)){
    return 0;
  }
  else if ((a>=45)&&(a<=55)){
    return 180;
  }
  else if ((a>=160)&&(a<=190)){
    return 270;
  }
  else if ((a>=610)&&(a<=660)){
    return 90;
  }
  else if ((a>=760)&&(a<=800)){
    return 45;
  }
  else if ((a>=430)&&(a<=470)){
    return 315;
  }
  else if ((a>=90)&&(a<=110)){
    return 225;
  }
  else if ((a>=280)&&(a<=310)){
    return 135;
  }
  else if ((a>=670)&&(a<=710)){
    return 22;
  }
  else if ((a>=510)&&(a<=550)){
    return 67;
  }
  else if ((a>=240)&&(a<=260)){
    return 112;
  }
  else if ((a>=40)&&(a<=44)){
    return 157;
  }
  else if ((a>=30)&&(a<=35)){
    return 202;
  }
  else if ((a>=60)&&(a<=70)){
    return 252;
  }
  else if ((a>=130)&&(a<=145)){
    return 292;
  }
  else if ((a>=400)&&(a<=435)){
    return 337;
  }
}
