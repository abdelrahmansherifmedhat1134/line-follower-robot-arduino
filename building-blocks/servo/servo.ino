#include <Servo.h>

Servo myservo;
void setup()
{
  myservo.attach(6);
}
int counter=0;
void loop()
{
  myservo.write(counter);
  delay(50);
  counter++;
  if(counter>180)
    for(counter=180;counter!=0;counter--)
  {
    myservo.write(counter);
 	delay(50);
  }
    
}