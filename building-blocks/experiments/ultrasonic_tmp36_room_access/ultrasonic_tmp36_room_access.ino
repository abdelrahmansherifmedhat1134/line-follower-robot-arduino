#define trig 2
#define echo 4
#define red 5
#define blue 6
#define green 7
#define temp_pin A5

int counter;

void check_print(float dist, float temp);
float distance(float time);
void reset_led();
void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600);
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
  
  //temp
  int value;
  float volt,temp;
  value=analogRead(temp_pin);
   volt=value*5.0/1024.0 ;
  temp= (volt-0.5)*100;
  
  //check values
  if(counter%100==0)
  check_print(distance,temp);
  counter++;
  
  //reset led
  reset_led();
  //if conditions
  if(distance<100)
  {
    if(temp>30)
    digitalWrite(red,1);
    
    else 
      digitalWrite(green,1);
  } 
  else
  digitalWrite(blue,1);
}


float calc_distance(float time)
{
  float disp;
  disp=0.0343*time/2 ;
    return disp ;
}

void check_print(float dist,float temp)
{
 
  Serial.print("distance is ");
  Serial.println(dist);
  Serial.print("temprature is ");
  Serial.println(temp);
  
   if(dist<100)
  {
    if(temp>30)
    Serial.println("Overheated room");
    
    else 
      Serial.println("Access granted");
  } 
  else
  Serial.println("Idle");

}

void reset_led()
{
  digitalWrite(blue,0);
  digitalWrite(red,0);
  digitalWrite(green,0);
}
