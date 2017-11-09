float flag=0,i=0,x1,x2,mini1=9999,mini2=9999,maxi1=0,maxi2=0,sum1=0,sum2=0;
float avg1,avg2;
String y;
int j=0;
void setup() 
{
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A5,INPUT);
}

void loop() 
{
  if(Serial.available()>0)
  {
    y=Serial.readString();
    if(y=="l")
    flag=1;
  }
  if(flag==1)
  {
    i++;
    if(i<=2000)
    {
      x1=analogRead(A0);
      if(x1<mini1)
      mini1=x1;
      if(x1>maxi1)
      maxi1=x1;
      sum1=sum1+x1;
      x2=analogRead(A5);
      if(x2<mini2)
      mini2=x2;
      if(x2>maxi2)
      maxi2=x2;
      sum2=sum2+x2;
     // Serial.print(x);
     // Serial.print("  ");
     // Serial.print(mini);
     // Serial.print("  ");
     // Serial.println(maxi);
    }
    else if(i>2000)
    {
      avg1=sum1/2000;
      avg2=sum2/2000;
      Serial.print(mini1);
      Serial.print(" ");
      Serial.print(maxi1);
      Serial.print(" ");
      Serial.print(avg1);
      Serial.print("       ");
      Serial.print(mini2);
      Serial.print(" ");
      Serial.print(maxi2);
      Serial.print(" ");
      Serial.print(avg2);
      Serial.print(" ");
      Serial.println(j++);
      flag=0;
      mini1=9999;mini2=9999;
      maxi1=0;maxi2=0;
      sum1=0;sum2=0;
      i=0;
    }
  }
  else if(flag==0)
  {
  }
}
