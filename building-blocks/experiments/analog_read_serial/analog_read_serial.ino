#define read A5
void setup()
{
  pinMode(read,INPUT);
  Serial.begin(9600);
}

void loop()
{
  int sig=analogRead(read);
  Serial.println(sig);
  delay(1000);
}