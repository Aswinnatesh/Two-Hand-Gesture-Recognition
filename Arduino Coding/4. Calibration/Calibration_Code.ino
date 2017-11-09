float flag=0,i=0,x,mini=9999,maxi=0,sum=0;
float avg;
String y;
int j=0;
void setup() 
{
  Serial.begin(9600);
  pinMode(A0,INPUT);
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
      x=analogRead(A0);
      if(x<mini)
      mini=x;
      if(x>maxi)
      maxi=x;
      sum=sum+x;
     // Serial.print(x);
     // Serial.print("  ");
     // Serial.print(mini);
     // Serial.print("  ");
     // Serial.println(maxi);
    }
    else if(i>2000)
    {
      avg=sum/2000;
      Serial.print(mini);
      Serial.print(" ");
      Serial.print(maxi);
      Serial.print(" ");
      Serial.print(avg);Serial.print(" ");
      Serial.println(j++);
      flag=0;
      mini=9999;
      maxi=0;
      sum=0;
      i=0;
    }
  }
  else if(flag==0)
  {
  }
}
