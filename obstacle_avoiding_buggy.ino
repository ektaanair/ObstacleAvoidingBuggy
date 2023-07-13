/*Obstacle Avoiding Buggy using Arduino Uno R3 with Sensor Shield v5.0 and an L298N H-Bridge Motor Controller. 
The buggy has a 2 DC mototrs that drive 2 of its wheels and a third wheel on the back on the acrylic body plate to provide extra support and mobility.
It uses an Ultrasonic Sensor monted onto a Servo at the front of the arculic body plate to gauge its whereabouts. */

#include <Servo.h> //Servo motor library

//Define pins for Motor A
int enA = 7;
int in1 = 8;
int in2 = 9;

//Define pins for Motor B
int enB = 5;
int in3 = 3;
int in4 = 4;

//Define sensor pins
const int trigPin = 13; 
const int echoPin = 12; 

//Define variables
long duration, distance, distanceFront, distanceRight, distanceLeft;
Servo servo_motor; //servo name


void setup(){
  //Set all motor pins as output to supply power to the DC motors to drive the wheels
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  servo_motor.attach(6); //Servo pin

  servo_motor.write(90); //Set servo to default front-facing position
  delay(200);
}

void loop(){
  //Check if there is space to move forward and do so if there is
  distanceFront=lookForward();

  if (distanceFront > 20)  {
    moveForward();
  }
 
  //If there is no space, stop moving. then move back slightly and check if there is space to the elft or the right.
  else {
    moveStop();
    delay(50);
    moveBackward();
    delay(300);
    moveStop();
    delay(50);
    distanceRight = lookRight();
    delay(100);
    distanceLeft = lookLeft();
    delay(100);

    //If there is more space to the right, turn right. Otherwise, turn left
    if (distanceRight >= distanceLeft){
      turnRight();
      delay(200);
      moveStop();
      delay(50);
    }
    else{
      turnLeft();
      delay(200);
      moveStop();
      delay(50);
    }
  }
  
}

//Function to check if there is space to move in front of the buggy
int lookForward(){
   servo_motor.write(90);
   delay(100); 

   //Clears the trigger pin
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);

  //Sets the trigger pin on HIGH state for 10 microseconds
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);

  //Reads the echo pin, return the sound wave travel time in microseconds
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   
   //Calculates distance using distance = speed of sound * time/2
   distance = duration/29/2;

   return distance;
  }

//Function to check if there is space to move to the right of the buggy
int lookRight(){  
  servo_motor.write(30);
  delay(200);
  //Clears the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //Sets the trigger pin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Reads the echo pin, return the sound wave travel time in microseconds
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
   
  //Calculates distance using distance = speed of sound * time/2
  distance = duration/29/2;

  servo_motor.write(90);

  return distance;
}

//Function to check if there is space to move to the left of the buggy
int lookLeft(){
  servo_motor.write(170);
  delay(200);
  //Clears the trigger pin
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);

  //Sets the trigger pin on HIGH state for 10 microseconds
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);

  //Reads the echo pin, return the sound wave travel time in microseconds
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   
   //Calculates distance using distance = speed of sound * time/2
   distance = duration/29/2;

  servo_motor.write(90);
  return distance;
}

//Function to stop the buggy
void moveStop(){
  
  analogWrite (enA, 0);
  analogWrite (enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

//Function to move forward
void moveForward(){
    
    analogWrite (enA, 200);
    analogWrite (enB, 200);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  
}

//Function to move backward
void moveBackward(){
  analogWrite (enA, 200);
  analogWrite (enB, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

//Function to turn right
void turnRight(){
  analogWrite (enA, 200);
  analogWrite (enB, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

//Function to turn left
void turnLeft(){
  analogWrite (enA, 200);
  analogWrite (enB, 200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

 
