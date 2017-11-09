#include <SoftwareSerial.h>
#include "MUX74HC4067.h"

MUX74HC4067 mux(7, 8, 9, 10, 11);

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
int val=0,i,k;
double dec=0,data[16],bin[16];
double threshold[16]={300,250,250,350,250,250,250,250,250,250,250,250,250,250,250,250};

void setup()
{
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  mux.signalPin(A0, INPUT, ANALOG);
  Serial.println("BLE - I'm the Master ! ");
  bluetooth.flush();
  bluetooth.setTimeout(500);
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
   }
  dec=0;
  
  for (i = 0; i < 16; i++)
  {
   dec = dec + ( bin[i] * pow(2,i));
  }
  if(dec>3)
  {
  dec=dec+1;
  }

  Serial.println("");
  Serial.print("Binary:");
  for(k=15;k>=0;k--)
    {
      Serial.print(int(bin[k]));
    }
  Serial.print("\t\t Decimal_A: ");
  Serial.print(long(dec));
  Serial.print("\t\t"); 
  Serial.print("Decimal_B: ");  
  

  if(bluetooth.available())  // If the bluetooth sent any characters
  {
    Serial.print(bluetooth.parseInt()); 
  bluetooth.flush();
   }
   
  delay(500);
}
