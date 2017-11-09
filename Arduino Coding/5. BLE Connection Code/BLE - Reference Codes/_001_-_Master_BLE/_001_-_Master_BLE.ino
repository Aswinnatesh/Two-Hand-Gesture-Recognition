#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

void setup() {
  Serial.begin(9600);
  Serial.println("Self Start - This is Master!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, I am Master Aswin");
  delay(1000);
}

void loop() {
  // run over and over
  if (mySerial.available()) 
  {
    Serial.write(mySerial.read());
  }
//  if (Serial.available())
//    mySerial.write(Serial.read());
}
