#define inp1 0
#define inp2 1
#define pwm  3
#define trig 10
#define echo 8

float distance(float time);


void setup()
{
  pinMode(inp1,OUTPUT);
  pinMode(inp2,OUTPUT);
  pinMode(pwm,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  
}


void loop()
{
  //ultrasonic
  float duration,distance;
  digitalWrite(trig,0);
  delayMicroseconds(5);
  digitalWrite(trig,1);
  delayMicroseconds(10);
  digitalWrite(trig,0);
  duration=pulseIn(echo,1);
  distance=calc_distance(duration);
  
  digitalWrite(pwm,255);
  
  if(distance<100)
  {
    digitalWrite(inp1,1);
    digitalWrite(inp2,1);
  }
  else
  {
    digitalWrite(inp1,1);
    digitalWrite(inp2,0);
  }
  
}


//functions
float calc_distance(float time)
{
  float disp;
  disp=0.0343*time/2 ;
    return disp ;
}
