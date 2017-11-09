void setup()
{
    Serial.begin(9600); 
}

void loop()
{

    int sensor, degrees;

    sensor = analogRead(0);

    Serial.print("analog input: ");

    Serial.print(sensor,DEC);
    
    Serial.print(" degrees: ");
    
    Serial.println(degrees,DEC);

    delay(100); 
}
