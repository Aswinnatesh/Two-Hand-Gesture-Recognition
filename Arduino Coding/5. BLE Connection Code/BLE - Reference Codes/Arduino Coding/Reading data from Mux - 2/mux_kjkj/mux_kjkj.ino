#include "MUX74HC4067.h"
MUX74HC4067 mux(7, 8, 9, 10, 11);

void setup()
{
  Serial.begin(9600);  // Initializes serial port
  mux.signalPin(A0, INPUT, ANALOG);
}

void loop()
{
  int data;
  for (byte i = 0; i < 16; ++i)
  {
    data = mux.read(i);

    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" is at : ");
   Serial.print(data);
    //Serial.print((double)(data) * 100 / 1023);
    Serial.println(" ");
  }
  Serial.println();
  
  delay(1500);
}

