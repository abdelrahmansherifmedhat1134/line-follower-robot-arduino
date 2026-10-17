#include <LiquidCrystal_I2C.h>

#define trig 3
#define echo 2
#define temp_pin A3

LiquidCrystal_I2C lcd(32,16,2);


int counter;

void check_print(float dist, float temp);
float distance(float time);

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.display();
  
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
  
  //reset lcd
  lcd.clear();
  //if conditions
  if(distance<100)
  {
    if(temp>30)
    
    lcd.print("Overheated room");
    
    else 
      lcd.print("Access granted");
  } 
  else
  lcd.print("Idle");
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






/*
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(32,16,2);

#define temp_pin A0

//motor A is the right wheel
// Motor Driver Pins 
#define ENA 5  // Motor A Enable
#define IN1 7  // Motor A Input 1
#define IN2 8  // Motor A Input 2
#define IN3 9  // Motor B Input 1
#define IN4 10 // Motor B Input 2
#define ENB 6  // Motor B Enable

// Sensor Pins 
#define SENSOR_LEFTMOST  A1
#define SENSOR_LEFT      A2
#define SENSOR_CENTER    A3
#define SENSOR_RIGHT     A4
#define SENSOR_RIGHTMOST A5
const int SENSOR_PINS[] = {SENSOR_LEFTMOST, SENSOR_LEFT, SENSOR_CENTER, SENSOR_RIGHT, SENSOR_RIGHTMOST};
const int NUM_SENSORS = 5;

#define TRIG_PIN 11
#define ECHO_PIN 12

#define calibrate_button 0
#define start_button 1

// Ultrasonic sensor variables
long lastPingTime = 0;
const int PING_INTERVAL = 100; // Time in milliseconds between pings
const int OBSTACLE_DISTANCE_CM = 100; // Stop if obstacle is closer than this

// State variable to handle obstacle detection
bool isObstacleDetected = false;

// PID Constants
// P (Proportional): Adjusts the motor speed based on the current error.
// I (Integral): Accounts for past errors, helping to eliminate steady-state error.
// D (Derivative): Predicts future error, damping oscillations.
double Kp = 1;
double Ki = 0;
double Kd = 0.5;

// PID variables
double lastError = 0;
double integral = 0;

// Base speed for the motors
int baseSpeed = 150; // Adjust this value between 0-255

// Sensor calibration variables
int sensorMin[NUM_SENSORS];
int sensorMax[NUM_SENSORS];
int sensorThresholds[NUM_SENSORS]; // Array to store individual thresholds

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print("hello");
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("this is");
  lcd.setCursor(0,1);
  lcd.print("a line follower");
  delay(500);
  lcd.clear();
  
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Set LINE FOLLOWER FORWARD
  digitalWrite(IN1, HIGH);   
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  // Configure ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  //config buttons
  pinMode(calibrate_button,INPUT_PULLUP);
  pinMode(start_button,INPUT_PULLUP);
  
  // Calibrate sensors
  calibrateSensors();
}

// Function to perform sensor calibration
void calibrateSensors() {
  Serial.println("Calibrating sensors...");
  lcd.print("calibrating ..");
  Serial.println("Calibration complete!");
  
  // Initialize min/max arrays with extreme values
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensorMin[i] = 1023;
    sensorMax[i] = 0;
  }
  
  // Rotate the robot to read sensor values
  // Turn left to expose sensors to both the line and the background
  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, 0); // Stops the left motor to turn right
  delay(1000); // we can adjust the calibration speed 

  // Keep turning and reading for a while
  long startTime = millis();
  while (millis() - startTime < 3000) { // Rotate for 3 seconds
    for (int i = 0; i < NUM_SENSORS; i++) {
      int sensorValue = analogRead(SENSOR_PINS[i]);
      if (sensorValue < sensorMin[i]) {
        sensorMin[i] = sensorValue;
      }
      if (sensorValue > sensorMax[i]) {
        sensorMax[i] = sensorValue;
      }
    }
  }

  // Stop the wheels 
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  // Calculate a midpoint threshold for each individual sensor
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensorThresholds[i] = (sensorMin[i] + sensorMax[i]) / 2;
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": Min=");
    Serial.print(sensorMin[i]);
    Serial.print(", Max=");
    Serial.print(sensorMax[i]);
    Serial.print(", Threshold=");
    Serial.println(sensorThresholds[i]);
  }
  lcd.setCursor(0,0);
  
  delay(2000); // Pause for 2 seconds before starting the loop
  lcd.clear();
}

// Function to check if a sensor is over the line
int lineDetected(int sensorIndex, int sensorValue) {
  // Returns 1 if the sensor is on the line (darker than the threshold), 0 otherwise
  return (sensorValue > sensorThresholds[sensorIndex]) ? 1 : 0;
}

// Function to read sensor values and determine the error
int readSensors() {
  // Read analog values from the sensors
  int s1 = lineDetected(0, analogRead(SENSOR_LEFTMOST));
  int s2 = lineDetected(1, analogRead(SENSOR_LEFT));
  int s3 = lineDetected(2, analogRead(SENSOR_CENTER));
  int s4 = lineDetected(3, analogRead(SENSOR_RIGHT));
  int s5 = lineDetected(4, analogRead(SENSOR_RIGHTMOST));
  
  // Weights for error calculation
  // A positive error means on the left.
  //A negative error means on the right.
  int error = s1 * -2 + s2 * -1 + s3 * 0 + s4 * 1 + s5 * 2;
  
  return error;
}


// Function to read ultrasonic sensor in a non-blocking way
float readUltrasonicSensor() {
  // Check if enough time has passed since the last ping
  if (millis() - lastPingTime >= PING_INTERVAL) {
    lastPingTime = millis();
    
    // Send dist signal
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    long duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration * 0.034 / 2;
    
    // Return the distance
    return distance;
  }
  return -1; // Return -1 if not enough time has passed
}


void loop() {
  float distance = readUltrasonicSensor();
 //temp
  int value;
  float volt,temp;
  value=analogRead(temp_pin);
  volt=value*5.0/1024.0 ;
  temp= (volt-0.5)*100;

  
  //reset lcd
  lcd.clear();
  
  // Update obstacle detection state based on the new reading
  if (distance != -1.0) {
    if (distance < OBSTACLE_DISTANCE_CM) {
      isObstacleDetected = true; // Set the flag to true
      Serial.println("OBSTACLE DETECTED! STOPPING!");
      
    } else {
      isObstacleDetected = false; // Obstacle is no longer there
    }
  }
  
  // Main control logic based on the obstacle state
  if (isObstacleDetected) 
  {
    // If an obstacle is detected, stop the robot
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    lcd.setCursor(0,0);
      lcd.print("object detected");
      if(temp>40)
      {
        lcd.setCursor(0,1);
        lcd.print("high temp");
      }
    else
    {
      lcd.setCursor(0,1);
      lcd.print("good temp");
    }
  } 
  else 
  {
    // If no obstacle, continue with line-following
    lcd.setCursor(0,0);
    lcd.print("NO object");
    if(temp>40)
    {
      lcd.setCursor(0,1);
      lcd.print("high temp");
    }
    else
    {
      lcd.setCursor(0,1);
      lcd.print("good temp");
    }  
    int error = readSensors();
    
    // Proportional term
    double proportional = error * Kp;
    
    // Integral term
    integral = integral + error;
    double integralTerm = integral * Ki;
    
    // Derivative term
    double derivative = error - lastError;
    double derivativeTerm = derivative * Kd;
    lastError = error;

    // PID output with multiplier restored
    double pidOutput = proportional + integralTerm + derivativeTerm;

    // Calculate motor speeds
    int motorSpeedA = baseSpeed - 25 * pidOutput;
    int motorSpeedB = baseSpeed + 25 * pidOutput;

    // Clamp motor speeds to the valid range (0-255)
    motorSpeedA = constrain(motorSpeedA, 0, 255);
    motorSpeedB = constrain(motorSpeedB, 0, 255);

    // For debugging
    Serial.print("Error: ");
    Serial.print(error);
    Serial.print(" | PID Output: ");
    Serial.print(pidOutput);
    Serial.print(" | Motor A: ");
    Serial.print(motorSpeedA);
    Serial.print(" | Motor B: ");
    Serial.print(motorSpeedB);
    Serial.println();
    if(error>0)
    {
      Serial.println("Right turn");
    }
    else if(error<0)
    {
      Serial.println("Left turn");
    }
    else if(error==0)
    {
      Serial.println("straight ahead");
    }
    
    // Write speeds to motors
    analogWrite(ENA, motorSpeedA);
    analogWrite(ENB, motorSpeedB);
  }
}


*/