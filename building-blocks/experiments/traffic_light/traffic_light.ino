// C++ code
//
#define red_led 1
#define yellow_led 2
#define green_led 3

void setup()
{
  pinMode(red_led,OUTPUT);
  pinMode(green_led,OUTPUT);
  pinMode(yellow_led,OUTPUT);
}

void loop()
{
  digitalWrite(green_led,HIGH);
  delay(4000);
  digitalWrite(green_led,LOW);
  digitalWrite(yellow_led,HIGH);
  delay(1500);
  digitalWrite(yellow_led,LOW);
  digitalWrite(red_led,HIGH);
  delay(4000);
  digitalWrite(red_led,LOW);
  
  
}