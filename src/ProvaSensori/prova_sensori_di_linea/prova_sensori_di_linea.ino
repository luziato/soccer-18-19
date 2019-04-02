#define pin1 A0
#define pin2 A5
int val1=0,val2=0;

void setup() 
{
  pinMode(pin1,INPUT);
  pinMode(pin2,INPUT);
  Serial.begin(9600);
}

void loop() 
{
  val1= analogRead(pin1);
  Serial.print(val1);
  Serial.print("\t");
  val2= analogRead(pin2);
  Serial.println(val2);


}
