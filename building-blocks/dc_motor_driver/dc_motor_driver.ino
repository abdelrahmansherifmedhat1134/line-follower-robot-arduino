#define ledOut A3 
#define inputPU 6  
#define buttonOut A4 
#define inp3 1
#define inp4 2
#define ena 3
#define pot A0
int potVal;
int potOutVal;
int motorState=00; 
int oldVal=1;
int newVal;
bool ledState=0;
void setup()
{
  pinMode(ledOut, OUTPUT);
  pinMode(inputPU,INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(inp3,OUTPUT);
  pinMode(inp4,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(pot,INPUT);
  analogWrite(ena,0);
  
}


void loop()
{
  if(motorState==01 || motorState==10)
  {
    potVal=analogRead(pot);
    potOutVal=map(potVal,0,1023,0,255);
    analogWrite(ena,potOutVal);
  }
  newVal=digitalRead(inputPU);
  Serial.println(newVal);
  if(oldVal==1 && newVal==0)
  {
    
    if(motorState==00)
    {
      analogWrite(ena,potOutVal);
      digitalWrite(inp4,1);
      digitalWrite(inp3,0);
      ledState=!ledState;
      digitalWrite(ledOut,ledState);
      motorState=01;
      
    }
    else if(motorState==01)
    {
      analogWrite(ena,potOutVal);
      digitalWrite(inp4,0);
      digitalWrite(inp3,1);
      motorState=10; 
      
      
    }
    else if(motorState==10)
    {
      analogWrite(ena,0);
      digitalWrite(inp4,1);
      digitalWrite(inp3,1);
      ledState=!ledState;
      digitalWrite(ledOut,ledState);
      motorState=00;
    }
  }
  oldVal=newVal;
    

}