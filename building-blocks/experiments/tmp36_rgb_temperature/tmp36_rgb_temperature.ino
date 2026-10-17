#define rgb 1
#define temp_sensor A5
#define red 3
#define blue 5
#define green 6
void close_led();
void setup()
{
  pinMode(temp_sensor,INPUT);
          
  pinMode(rgb,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(green,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  float temp,voltage;
  int sensor_value;
  sensor_value=analogRead(temp_sensor);
  voltage=sensor_value*5.0/1024.0;
  temp= (voltage-0.5)*100;
  Serial.println(temp);
  delay(100);

if(temp<=20)
  {
    close_led();
    digitalWrite(blue,1);
  }
  else if(temp>20 && temp<31)
  {
    close_led();
    digitalWrite(green,1);
  }
  else if(temp>30)
  {
    close_led();
    digitalWrite(red,1);
  }
}
void close_led()
{
  digitalWrite(blue,0);
  digitalWrite(red,0);
  digitalWrite(green,0);
}


