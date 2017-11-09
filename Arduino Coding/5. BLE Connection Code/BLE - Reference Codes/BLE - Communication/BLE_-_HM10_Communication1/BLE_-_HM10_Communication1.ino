
#include <SoftwareSerial.h>
#include "MUX74HC4067.h"

MUX74HC4067 mux(7, 8, 9, 10, 11);

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3
int x=0;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

double dec=0,data[16],bin[16];int i; 
double threshold[16]={300,250,250,250,250,250,250,250,250,250,250,250,250,250,250,250};

void setup()
{
  Serial.begin(9600);  // Begin the serial monitor at 9600bps

mux.signalPin(A0, INPUT, ANALOG);
  Serial.println("BLE - I'm the Slave ! ");

  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  
  delay(100);
}

void loop()
{
//  if(bluetooth.available())  // If the bluetooth sent any characters
//  {
//    // Send any characters the bluetooth prints to the serial monitor
//    Serial.print((char)bluetooth.read());  
//  }

  //if(Serial.available())  // If stuff was typed in the serial monitor
  //{
    
    // Send any characters the Serial monitor prints to the bluetooth
    
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
  Serial.print("\t\t\t Decimal: ");
  Serial.println(dec); //dec=0;
  //mySerial.println(dec);
  delay(1500);
    
    //bluetooth.print((char)dec);
    x=dec;
    bluetooth.println(x);
    dec=0;
//}
  // and loop forever and ever!
}
