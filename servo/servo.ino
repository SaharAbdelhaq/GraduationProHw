// last update working good

#include <Servo.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

// Define the servo pins
const int servoPin2 = 8;
const int servoPin3 = 9;
const int servoTrabpin = 7;
const int servoSeedpin1 = 6;
const int servoSeedpin2 = 5;


//IR1
int IRsensor1 = 2;              // the pin that the first IR sensor is attached to
int IRsensor2 = 3;              // the pin that the second IR sensor is attached to
int IRsensor3 = 4;              // the pin that the second IR sensor is attached to



AccelStepper stepper(AccelStepper::FULL4WIRE, A0, A1, A2, A3); // Adjust the pin numbers accordingly

// Create servo objects
Servo servo2;
Servo servo3;
Servo servoTrab;
Servo servoSeed1;
Servo servoSeed2;


// Servo positions
const int openPosition2 = 90;   // Open position for servo2 in degrees
const int openPosition3 = 90;   // Open position for servo3 in degrees
const int openTrab = 140;   // Open position for servo3 in degrees
const int openSeed1 = 80;   // Open position for servo3 in degrees
const int openSeed2 = 80;   // Open position for servo3 in degrees


bool continuousRotation = false;

void setup() {
  Serial.begin(9600);
  
  // Attach the servo objects to their respective pins
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servoTrab.attach(servoTrabpin);
  servoSeed1.attach(servoSeedpin1);
  servoSeed2.attach(servoSeedpin2);


  // Set initial positions of the servos
  servo2.write(0);
  servo3.write(0);
  servoTrab.write(0);
  servoSeed1.write(0);
  servoSeed2.write(0);


  // Set the maximum speed and acceleration of the motor
  stepper.setMaxSpeed(10);     // Adjust the maximum speed as needed
  stepper.setAcceleration(100); // Adjust the acceleration as needed
  stepper.setCurrentPosition(0); // Set the initial position to 0 degrees

  //IR
  pinMode(IRsensor1, INPUT);    // initialize sensor1 as an input
  pinMode(IRsensor2, INPUT);    // initialize sensor2 as an input
  pinMode(IRsensor3, INPUT);    // initialize sensor2 as an input

}


 void loop() {
   

  resetServos();

  if (digitalRead(IRsensor1) == LOW) {
      Serial.println("LOWWWWWWW"); 
    openServos23();
 StepperMoving(true); // Rotate the stepper motor continuously
}

 if (digitalRead(IRsensor2) == LOW) {
    openTrabServo();
    //  continuousRotation = true; 
       servoTrab.write(0);
    //      StepperMoving(true); // Rotate the stepper motor continuously



}
if(digitalRead(IRsensor3) == LOW){
  // open a seed servo
    openTrabServo();
  
    // continuousRotation = false;     
    // StepperMoving(false); 


}

}

void openServos23() {
  servo2.write(openPosition2);
  servo3.write(openPosition3);
}

void openTrabServo() {
  servoTrab.write(openTrab);
  delay(5000);

}


void openSeedServo() {
  servoSeed1.write(servoSeedpin1);
  delay(5000);

}

void resetServos() {
  // Reset the servos to the initial position
  servo2.write(0);
  servo3.write(0);
  servoTrab.write(0);
  servoSeed1.write(0);
  servoSeed2.write(0);
  
  
}

// Function to move the stepper motor to the right about 90 degrees
void StepperMoving(bool continuousRotation) {
  // Get the current position of the stepper motor
  static int currentPosition = 0;
  // Set the speed and direction of the stepper motor
  stepper.setSpeed(200); // Adjust the speed as needed
  
  // Run the motor continuously in one direction if continuousRotation is true
  if (continuousRotation) {
    while (digitalRead(IRsensor2) == HIGH) {
      stepper.runSpeed();
    }
     while (digitalRead(IRsensor1) == LOW) {
      stepper.runSpeed();
    }
  }

    // Run the motor continuously in one direction if continuousRotation is true
  if (continuousRotation) {
    while (digitalRead(IRsensor3) == HIGH) {
      stepper.runSpeed();
    }
  }
  // Stop the stepper motor when continuousRotation is false or IRsensor3 detects an object
  stepper.stop();
  // Update the current position (optional, depending on your use case)
  currentPosition = stepper.currentPosition();
}

