//int ip[16];//Binary Input
int dec;//Decimal Output
int i;
String x;
char y;

void setup() {
  Serial.begin(9600);

}

void loop() {

  //Serial.println("Enter the binary no");

   int ip[16]={1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1};
   
   BintoDec(ip);
}

void BintoDec(int bin[])
{

    for (i = 0; i < 15; i++)
    {
      dec = dec + ( bin[i] * (2 ^ i)); //Pow(2,i)
    }
    Serial.println(dec);//Print the Output
    dec = 0;
    
}

