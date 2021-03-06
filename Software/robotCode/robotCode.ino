// Global variables, these need to be referenced throughout the code
#include <Servo.h>  // Allows servos to be used; Servo module
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;

// Assign LED's to choosen out pin's
const int activityLight = 4;
const int posSaveLight = 2;
const int errorLight = 1;
const int safetyStopLight = 7;

// Assign Buzzer pin and PIR ppin
const int buzzerPin = 10;
const int pirPin = 10;
int pirState = LOW;
boolean pirSafetyVal = false;
boolean safetyStopVal = false;
int pirTriggers = 0;  // This is the number of low to high triggers on the PIR

// Sets up variable for buttons, which are used for commands
const int posSaveButton = 13;
const int posRunButton = 12;
const int safetyButton = 8;

int posSaveButtonPresses = 0;
boolean posRunButtonIsPressed = false;
boolean safetyButtonVal = false;

// Rotary potentiometer setup to allow for manual control of servos
const int basePot = A0;  // Pin for base potentiometer
const int shoulderPot = A1;  // Pin for shoulder potentiometer
const int elbowPot = A2;  // Pin for elbow potentiometer
// Angles and values for each servo-pot combo. Angles for servos, vals for potentiometers
int basePotVal;
int basePotAngle;
int shoulderPotVal;
int shoulderPotAngle;
int elbowPotVal;
int elbowPotAngle;

// Below are the saved positions for the three servo's, these are cycled when posRunButtonIsPressed = true
int baseServoSavedPos[] = {1,1,1,1,1};
int shoulderServoSavedPos[] = {1,1,1,1,1};
int elbowServoSavedPos[] = {1,1,1,1,1};
// Defaults for all are {1,1,1,1,1} (five positions, for five saves in memory)

void setup() {
  // Setup pins for LED's (outputs) and pins for buttons (inputs)
  pinMode(activityLight, OUTPUT);
  pinMode(posSaveLight, OUTPUT);
  pinMode(errorLight, OUTPUT);
  pinMode(safetyStopLight, OUTPUT);
  pinMode(posSaveButton, INPUT);
  pinMode(posRunButton, INPUT);
  pinMode(safetyButton, INPUT);
  // Setup pins for PIR and buzzer
  pinMode(buzzerPin, OUTPUT);  // This is for the warning buzzer
  pinMode(pirPin, INPUT);  // Sets the PIR input pin as an input

  Serial.begin(9600);
}

// Function used to check if the robot workspace is safe for movement
// three variables passed to function are the servo positions before run
void pirSafetyCheck(int baseInitialPos, int shoulderInitialPos, int elbowInitialPos) {
  // Check if pir has been triggered
  if(pirState = LOW) {
    if(pirState = HIGH) {
      pirTriggers++;
    }
  }
  // This function is supposed to run only after every baseServo run, to ensure proper detection
  // If function runs before baseServo, then it might stop the machine

  //Below interupts servo movement
  if(pirTriggers >= 2) {
    digitalWrite(buzzerPin, HIGH);  // Rings buzzer
    safetyStopVal = true;  // Triggers safety values
    pirSafetyVal = true;  // Triggers safety values
    baseServo.write(baseInitialPos);  // Overwrites servo position
    shoulderServo.write(shoulderInitialPos);  // Overwrites servo position
    elbowServo.write(elbowInitialPos);  // Overwrites servo position
    delay(3000);  //Stops for 3 seconds
  }
  if(pirSafetyVal == true) {
    if(pirState == LOW) {
      delay(100);
      if(pirState == LOW) {
        safetyStopVal = false;
        pirSafetyVal = false;
      }
    }
    else {
      safetyStopVal = true;
      pirSafetyVal = true;
    }
  }
}

void loop() {
//--------------------------------------------------------------------------------------------
  if(digitalRead(safetyButton) == HIGH) {
    // This function is a toggle for the safety stop button; toggles true or false
    if(safetyStopVal == false) {
      safetyStopVal = true;
    }
    if(safetyStopVal = true) {
      safetyStopVal = false;
    }
  }
  // Below reads the value of potentiometers and then maps them to degrees for the servos to move to
  basePotVal = analogRead(basePot);
  basePotAngle = map(basePotVal, 0, 1023, 0, 179);
  shoulderPotVal = analogRead(shoulderPot);
  shoulderPotAngle = map(shoulderPotVal, 0, 1023, 0, 179);
  elbowPotVal = analogRead(elbowPot);
  elbowPotAngle = map(elbowPotVal, 0, 1023, 0, 179);
  // Below runs the servos to the potentiometer positions
  baseServo.write(basePotAngle);
  shoulderServo.write(shoulderPotAngle);
  elbowServo.write(elbowPotAngle);
//-------------------------------------------------------------------------------------------- 
  if(digitalRead(posSaveButton) == HIGH) {
    // Checks if the position save button has been pressed
    posSaveButtonPresses++;
    switch (posSaveButtonPresses) {  // Executes a different case depending on how many times the button is pressed
      case 1:  // Saves potentiometer positions to servo angles memory 1
        baseServoSavedPos[0] = basePotAngle;
        shoulderServoSavedPos[0] = shoulderPotAngle;
        elbowServoSavedPos[0] = elbowPotAngle;
        break;
      case 2:  // Saves potentiometer positions to servo angles memory 2
        baseServoSavedPos[1] = basePotAngle;
        shoulderServoSavedPos[1] = shoulderPotAngle;
        elbowServoSavedPos[1] = elbowPotAngle;
      case 3:  // Saves potentiometer positions to servo angles memory 3
        baseServoSavedPos[2] = basePotAngle;
        shoulderServoSavedPos[2] = shoulderPotAngle;
        elbowServoSavedPos[2] = elbowPotAngle;
      case 4:  // Saves potentiometer positions to servo angles memory 4
        baseServoSavedPos[3] = basePotAngle;
        shoulderServoSavedPos[3] = shoulderPotAngle;
        elbowServoSavedPos[3] = elbowPotAngle;
      case 5:  // Saves potentiometer positions to servo angles memory 5
        baseServoSavedPos[4] = basePotAngle;
        shoulderServoSavedPos[4] = shoulderPotAngle;
        elbowServoSavedPos[4] = elbowPotAngle;
    }
  }
  if(digitalRead(posRunButton) == HIGH) {
    posRunButtonIsPressed = true;
  }

  if(posRunButtonIsPressed == true) {
    // Runs through memory positions
    // Checks safety of work environment, passes the first memory saved position as the initial position
    pirSafetyCheck(baseServoSavedPos[0], shoulderServoSavedPos[0], elbowServoSavedPos[0]);
    if(safetyStopVal == false) {
      for(int i = 0; i<5; i++) {  // Cycles through each memory position for servo
        // Moves each servo to it's ith memory position
        baseServo.write(baseServoSavedPos[i]);
        shoulderServo.write(shoulderServoSavedPos[i]);
        elbowServo.write(elbowServoSavedPos[i]);
        delay(1050);  // Stops robot operations for 1.5 secons)
      }
    }
  }
  delay(300);  // Stops robot for 0.3 seconds
}
