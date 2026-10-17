#define pot A5
#define pot_led 3

#define ldr A0
#define ldr_led 10 

void setup()
{
  pinMode(pot,INPUT);
  pinMode(pot_led,OUTPUT);
  
  pinMode(ldr,INPUT);
  pinMode(ldr_led,OUTPUT);
}

void loop()
{
  int pot_led_brightness=analogRead(pot);
  pot_led_brightness= map(pot_led_brightness,0,1023,0,255);
  analogWrite(pot_led,pot_led_brightness);
  
  int ldr_led_brightness=analogRead(ldr);
  ldr_led_brightness= map(ldr_led_brightness,325,1023,0,255);
  analogWrite(ldr_led,ldr_led_brightness);
}