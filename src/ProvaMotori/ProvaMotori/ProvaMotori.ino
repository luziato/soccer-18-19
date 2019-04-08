//j0={23,28,3}-->dietro
//j1={22,27,2}-->destra
//j2={24,29,4}-->sinistra
int dira=13,dirb=12,pwm=11;
void setup() 
{
  pinMode(dira,OUTPUT);
  pinMode(dirb,OUTPUT);
  pinMode(pwm,OUTPUT);
  Serial.begin(9600);
  Serial.println("Serial initialized...");
  digitalWrite(pwm,255);

}

void loop() 
{
  digitalWrite(dira,1);
  delay(100);
  digitalWrite(dira,0);
  delay(100);
}
