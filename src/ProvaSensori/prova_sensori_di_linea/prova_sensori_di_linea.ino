#define pin A0
int val=0;

void setup() 
{
  pinMode(pin,INPUT);
  Serial.begin(9600);
}

void loop() 
{
  val= analogRead(pin);
  Serial.println(val);

}
