#include <SoftwareSerial.h>

int sensorValue = 0;  // variable to store the value coming from the sensor
SoftwareSerial mySerial(3, 2); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.print("AT+ROLE1"); 
  delay(100);
  Serial.println("BLE - I'm the Master");
}

void loop() {
  
  if (mySerial.available())
  { 
  Serial.print("Received data: ");
  while (mySerial.available())  {
  Serial.write(mySerial.read());
  }
  Serial.println("");
  }
  delay(1000);                  
}
