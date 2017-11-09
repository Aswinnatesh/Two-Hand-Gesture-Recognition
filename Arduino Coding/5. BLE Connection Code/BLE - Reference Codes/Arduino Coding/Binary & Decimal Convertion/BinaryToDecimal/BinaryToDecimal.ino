int bin[16];//Binary Input
int dec;//Decimal Output
int i;
String x;
char y;

void setup() {
  Serial.begin(9600);

}

void loop() {

  //Serial.println("Enter the binary no");

  if (Serial.available() > 0)
  {
    x = Serial.readString();//Read the input

    for (i = 0; i < 15; i++)
    {
      y = x.charAt(i);
      int m = (int)y;
      bin[i] = m;
    }

    for (i = 0; i < 15; i++)
    {
      dec = dec + ( bin[i] * (2 ^ i)); //Pow(2,i)
    }
    Serial.println(dec);//Print the Output
    dec = 0;
  }

}
