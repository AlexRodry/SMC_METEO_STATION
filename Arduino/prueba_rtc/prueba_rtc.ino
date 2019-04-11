#include <Wire.h>
#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;

void setup(){
  Serial.begin(9600);
  clock.begin();
  clock.setDateTime(2019,04,05,9,10,00);
}

void loop(){
  dt = clock.getDateTime();
  Serial.print(dt.year);Serial.print("-");Serial.print(dt.month);Serial.print("-");Serial.print(dt.day);Serial.print("/");
  Serial.print(dt.hour);Serial.print(":");Serial.print(dt.minute);Serial.print(":");Serial.println(dt.second);
  delay(1000);
}


/*#include <RTClib.h>
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
#include <Wire.h>
void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  DateTime now = rtc.now();
  Serial.print(now.year(),DEC);
  Serial.print("/");
  Serial.println(now.second(),DEC);
  delay(1000);
}*/
