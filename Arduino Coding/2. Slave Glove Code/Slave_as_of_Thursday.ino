
#include <SoftwareSerial.h>
#include "MUX74HC4067.h"

MUX74HC4067 mux(7, 8, 9, 10, 11);

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3
int x=0,y=0;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

long dec=0,dec1=0,dec2=0,data[16],bin[18],temp=0;
int i,k=0,m=0;
int datas;
double threshold[16]={180,135,220,210,670,190,320,420,580,750,592,638,250,250,250,250};
//double threshold[16]={1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023,1023};
//double fix[7]={820,720,615,410,310,508,206};
double fix[7]={800,720,615,410,310,508,206};
double t[7];

void setup()
{
  for ( i = 0; i < 18; i++)
  {
    bin[i]=0;
   
  }
  
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  mux.signalPin(A0, INPUT, ANALOG);
  Serial.println("BLE - I'm the Slave ! ");
  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  delay(100);
  
   for(i=0;i<10;i++)
  {
 
  for (k = 9; k < 16;k++)
  {
    datas = mux.read(k);

   m=k-9;
    if(k==11)
    {
      m=6;
    }
    if(k==15)
    {
      m=2;
    }
    fix[m]=datas;
   
  }
   delay(300);
  }

   for(i=0;i<7;i++)
  {
   Serial.println(fix[i]);
  }
 delay(5000);
}

void loop()
{
 //Flex Sensors:
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
  temp=data[11];
  data[11]=data[15];
  data[15]=temp;
  
  for ( i = 9; i < 18; i++)
  {
    bin[i] = 0;
  }
  
   for ( i = 9; i <16; i++)
  {
    
    //for(j=9;j<16;j++)
    //{
     for(k=i+1;k<16;k++)
    {
     //if(data[i]==data[k])
    if(abs(data[i]-data[k])<=5) 
     {
     //flag[j]++;         
     //entry[k][1]=1;
     
     bin[i]=1;
     bin[k]=1;
     
     }
      
    } 
    //}
  

     if( i==15 )
    {
      //Serial.println(data[i]);
      if( data[i]<(fix[6]-5) )
      {
        bin[i+1]=1;
        bin[i+2]=0;
      }
      else if( data[i]>(fix[6]+5))
      {
        bin[i+1]=0;
        bin[i+2]=1;
      }
      else
      {
        bin[i+1]=0;
        bin[i+2]=0;
      }
    }
  }
  
  bin[15]=0;
  for ( i = 9; i <15; i++)
  {
      k=i-9;
    if( abs(fix[k]-data[i])>=20)
    {
     bin[i]=1; 
    }
//    else
//    {
//      bin[i]=0;
//    }
  }
  
  
  //BinaryTODecimal:
  dec1=0;
  dec2=0;
  
  for ( i = 0; i <=8; i++)
  {
   dec1 = dec1 + ( bin[i] * pow(2,i));
  }

 for ( i = 9; i <=17; i++)
  {
   dec2 = dec2 + ( bin[i] * pow(2,i-9));
  }
  
Serial.print("Binary:");

 for(k=17;k>=9;k--)
 {
  Serial.print(int(bin[k]));
 }
 Serial.print("\t");
for(k=8;k>=0;k--)
 {
  Serial.print(int(bin[k]));
 }
 
if(dec1>3)
{
dec1=dec1+1;
}
if(dec2>3)
{
dec2=dec2+1;
}

dec=(512*dec2)+dec1;
//Serial.println("");
//Serial.println((long)dec1);
//Serial.println((long)dec2);
//Serial.println("");
 //Printing:
  Serial.print("\t\t\t Decimal: ");
  
  Serial.println(long(dec)); //dec=0;
  //mySerial.println(dec);   
    //bluetooth.print((char)dec);
    x=(int)dec1;
    y=(int)dec2;
//Serial.println("");
//Serial.println(x);
//Serial.println(y);
//Serial.println("");
 bluetooth.println(y);
 bluetooth.println(x); 
    
//    if(x%2==0)
//{
// unsigned int y=x/2;
// Serial.println(y);
// bluetooth.println(y);
// bluetooth.println(y);
// 
//}

    //bluetooth.println(x);
   // bluetooth.print('f');
    dec=0;
  delay(500);
}
