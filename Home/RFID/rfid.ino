#include<SoftwareSerial.h>
String rfid;
SoftwareSerial mySerial(9,10);
void setup() {
mySerial.begin(9600);
Serial.begin(9600);
pinMode(13, OUTPUT);
pinMode(12, OUTPUT);
}

void loop() {

while(mySerial.available()){
  delay(10);
  char c= mySerial.read();
  rfid += c;
  }
Serial.print(rfid);
 if(rfid=="6D0035E8CA7A")
 {
  Serial.println("Working!"); //door opens
  digitalWrite(13,1);
  digitalWrite(12,0);
  delay(1000);
  digitalWrite(13,0);
  digitalWrite(12,0);
 
  }
  
  rfid="";
  
}

