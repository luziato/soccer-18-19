#define pin1 A0
int val1=0;

void setup() 
{
  pinMode(pin1,INPUT);
  
  Serial.begin(9600);
}

void loop() 
{
  val1= analogRead(pin1);
  Serial.print(val1);
  Serial.println(" ");


}
