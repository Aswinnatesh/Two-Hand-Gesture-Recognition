#include <SoftwareSerial.h>
#include "MUX74HC4067.h"

MUX74HC4067 mux(7, 8, 9, 10, 11);

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
int i,k;
int val1=0,val2=0;
long val=0;
double dec=0,data[16],bin[18],temp=0;
//double threshold[16]={1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023};
double threshold[16]={380,260,320,320,380,240,240,220,240,250,250,250,250,250,250,250};
double clk=0,sum=0,prev_clk=0;int flag=0,count=0;

void setup()
{
  
  for ( i = 0; i < 18; i++)
  {
    bin[i]=0;
   
  }
  
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  mux.signalPin(A0, INPUT, ANALOG);
  Serial.println("BLE - I'm the Master ! ");
  bluetooth.flush();
  bluetooth.setTimeout(15);
}

void loop()
{
  clk=millis();
  sum=sum+clk-prev_clk;
 //Flex sensors:
  for ( i = 0; i < 9; i++)
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
  
//Contact sensors:
//Thumb i=15
   for ( i = 9; i < 16; i++)
  {
    data[i] = mux.read(i);
  }
  temp=data[12];
  data[12]=data[15];
  data[15]=temp;
  
   for ( i = 9; i <16; i++)
  {
    
    if( data[i]>10 && i!=15 )
    {
     bin[i]=1;
    }
    else if( data[i]==0 && i!=15 )
    {
      bin[i]=0;
    }


     if( i==15 )
    {
      //Serial.println(data[i]);
      if( data[i]<95 )
      {
        bin[i+1]=0;
        bin[i+2]=1;
      }
      else if( data[i]>110 )
      {
        bin[i+1]=1;
        bin[i+2]=0;
      }
      else
      {
        bin[i+1]=0;
        bin[i+2]=0;
      }
    }
  }
bin[15]=0;

 //Serial.println(data[15]);
 
 //BinaryTODecimal:
  dec=0;
  for (i = 0; i <=17; i++)
  {
   dec = dec + ( bin[i] * pow(2,i));
  }
//  if(dec>3)
//  {
// // dec=dec+1;
//  }


if(sum>=3000)
  {
    flag++;
    if(flag==1)
    {
    Serial.println("");
    Serial.print("Do the Gesture...\t\t");
    sum=0;
    }
    else if(flag==2)
    {
  Serial.print("BinaryA:");
  for(k=17;k>=9;k--)
    {
      Serial.print(int(bin[k]));
    }
      Serial.print("\t\t");
      for(k=8;k>=0;k--)
    {
      Serial.print(int(bin[k]));
    }
    Serial.print("\t\t");

 //Printing:  
  Serial.print("\t\t Decimal_A: ");
  Serial.print(long(dec));
  Serial.print("\t\t"); 
  Serial.print("Decimal_B: ");  
  Serial.print((long)val);
  count++;
  Serial.print("\t\t");
  Serial.print(count);
    flag=0;
    sum=0;
    }
  }





 //Bluetooth:
  if(bluetooth.available())  // If the bluetooth sent any characters
  {
   val1=bluetooth.parseInt();
   val2=bluetooth.parseInt();
   bluetooth.flush();
   }
//   Serial.println("");
//   Serial.println(val1); 
//   Serial.println(val2);
//   Serial.println(""); 
  long tm1=512;
  long tm2=(long)val1;
  long tm=tm1*tm2;
  long tm3=(long)val2;
  
  val=tm+tm3; 
  delay(500);
    prev_clk=clk;
}
