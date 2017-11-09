
#include <SoftwareSerial.h>
#include "MUX74HC4067.h"

MUX74HC4067 mux(7, 8, 9, 10, 11);

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3
int x=0;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

double dec=0,data[16],bin[16];
int i,k; 
double threshold[16]={300,250,250,250,250,250,250,581,582,750,592,638,250,250,250,250};

void setup()
{
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  mux.signalPin(A0, INPUT, ANALOG);
  Serial.println("BLE - I'm the Slave ! ");
  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
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
  }
  dec=0;
  for ( i = 0; i < 16; i++)
  {
   dec = dec + ( bin[i] * pow(2,i));
  }
Serial.print("Binary:");

 for(k=15;k>=0;k--)
 {
  Serial.print(int(bin[k]));
 }
 
if(dec>3)
{
dec=dec+1;
}
  Serial.print("\t\t\t Decimal: ");
  Serial.println(long(dec)); //dec=0;
  //mySerial.println(dec);   
    //bluetooth.print((char)dec);
    x=(int)dec;
    bluetooth.println(x);
   // bluetooth.print('f');
    dec=0;
  delay(50);
}
