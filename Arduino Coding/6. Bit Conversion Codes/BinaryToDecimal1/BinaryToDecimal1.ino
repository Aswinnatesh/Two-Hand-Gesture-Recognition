//int bin[16];//Binary Input
long dec=0;//Decimal Output
int i,len;
String x;
char y;
int bin[16]={0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0};

void setup() {
  Serial.begin(9600);

//for(i=0;i<16;i++)
//{
//  bin[i]=1;
//}



}

void loop() {

  //Serial.println("Enter the binary no");

//  if (Serial.available() > 0)
//  {
//    x = Serial.readString();//Read the input
//    Serial.println(x);
//len=x.length();
//    for (i = 0; i < len; i++)
//    {
//      y = x.charAt(i);
//      //Serial.println(x);
//      int m = (int)y;
//      bin[i] = m;
//    }

    for (i = 0; i < 16; i++)
    {
      dec = dec + ( bin[i] * pow(2,i)); //Pow(2,i)
    }
    Serial.println(dec);//Print the Output
    dec = 0;
//    for(i=0;i<16;i++)
//  {
//    bin[i]=0;
//  }
//    
//  }

}
