/*
 
 This example code is in the public domain.
 
 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // RX, TX
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
 
  


  Serial.println("Self Start - This is Slave! ");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  // set slave
//  mySerial.print("AT+ROLE0"); 
  //delay(10000);

 
}

void loop() // run over and over
{
  
    sensorValue = analogRead(sensorPin);
    // set the data rate for the SoftwareSerial port
    mySerial.println("Aswin");
    //mySerial.println(sensorPin);
    //Serial.println(sensorPin);
  //mySerial.print(" Hi, I am the Sender ");
  //delay(1000);  
//  if (mySerial.available())
//    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}
