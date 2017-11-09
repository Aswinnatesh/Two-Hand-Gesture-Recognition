int i, x, t1, p, rem, j,k;

int ip;//Decimal input
int bin[16], binary[16];//Binary Output


void setup() {
  Serial.begin(9600);

}

void loop() {

  ip=732;

  DectoBin(ip);
 
}


void DectoBin(int dec)
{
//Serial.println("Enter the decimal no");

    i = 0;
    x = 0;
    
    //dec = Serial.parseInt();//Read the Input
   int t=dec;
   
    while (t > 0)
    {
      if ( t % 2 == 0)
      {
        rem = 0;
      }
      else
      {
        rem = 1;
      }
      t = dec / 2;

      bin[i++] = rem;

    }

    /* //To Append n 0's to the Binary no in the starting to make it 16 Bit :
     if(sizeof(bin)<16)
    {
      int n= 16-i;
    for(x=0;x<n;x++)
    {
    binary[x]=0;
    }

    }
    */

    i = i - 1;

    for (j = i; j >= 0; j--)
    {
      binary[x] = bin[j];
      x++;
    }

    //Serial.println("The decimal no is:");
    for (p = 0; p < 16; p++)
    {
      Serial.print(binary[p]);//Print the Output
    }
    Serial.println("\n");

  

}

