#include <SoftwareSerial.h>
#include "MUX74HC4067.h"

MUX74HC4067 mux(7, 8, 9, 10, 11);
SoftwareSerial mySerial(2, 3); // RX, TX

double dec=0,data[16],bin[16];int i; 
double threshold[16]={300,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250};
void setup()
{
  Serial.begin(9600);  // Initializes serial port
  mux.signalPin(A0, INPUT, ANALOG);
  Serial.println("BLE - I'm the Slave ! ");
  mySerial.print("AT+ROLE0"); 
  delay(100);
 }

void loop()
{ 
 
  for ( i = 0; i < 16; i++)
  {
    data[i] = mux.read(i);
    if(data[i]>threshold[i])
    {
    bin[i]=1;
    }
    else
    {
    bin[i]=0;
    }
    dec = dec + ( bin[i] * pow(2,i));
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" is at : ");
   Serial.print(bin[i]);
    //Serial.print((double)(data) * 100 / 1023);
    Serial.println(" ");
  }
  dec=0;
  for ( i = 0; i < 16; i++)
  {
   dec = dec + ( bin[i] * pow(2,i));
  }
  Serial.print("/tDecimal: ");
  Serial.println(dec); dec=0;
  mySerial.println(dec);
  delay(1500);
}






