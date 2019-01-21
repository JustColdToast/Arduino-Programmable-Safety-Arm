// Global variables, these need to be referenced throughout the code
#include <Servo.h>  // Allows servos to be used; Servo module
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;

// Assign LED's to choosen out pin's
const int activityLight = 4;
const int posSaveLight = 2;
const int errorLight = 11;
const int safetyStopLight = 7;

// Assign Buzzer pin and PIR pin
const int buzzerPin = 10;
const int pirPin = 9;
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
  // Setup servos
  baseServo.attach(3);
  shoulderServo.attach(6);
  elbowServo.attach(5);
  // setup pots
  pinMode(basePot, INPUT);
  pinMode(shoulderPot, INPUT);
  pinMode(elbowPot, INPUT);
  
  digitalWrite(errorLight, LOW);
  
  Serial.begin(9600);
}

void safeCheck() {
  if(digitalRead(pirPin)==LOW) {
      if(digitalRead(pirPin)==HIGH) {
        pirTriggers++;
        Serial.print('PIR Triggered');
        digitalWrite(errorLight, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(300);
        digitalWrite(errorLight, LOW);
        digitalWrite(buzzerPin, LOW);
      }
  }
  if(pirTriggers>=1) {
    pirSafetyVal = true;
    safetyStopVal = true;
    digitalWrite(safetyStopLight, HIGH);
  }
}
// Function that runs through motors while looking at safety value
void motorRun(int sPos1, int i) {
  if(digitalRead(pirPin)==LOW) {
    if(digitalRead(pirPin)==HIGH) {
      pirTriggers++;
      Serial.print('PIR Triggered');
      digitalWrite(errorLight, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(300);
      digitalWrite(errorLight, LOW);
      digitalWrite(buzzerPin, LOW);
    }
  }
  baseServo.write(baseServoSavedPos[i]);
  digitalWrite(activityLight, HIGH);
  delay(300);
  if (pirTriggers <1) {
    safeCheck();
    if ((safetyStopVal == false) && (digitalRead(pirPin) == LOW)) {
      shoulderServo.write(shoulderServoSavedPos[i]);
        safeCheck();
    }
    if ((safetyStopVal == false) && (digitalRead(pirPin) == LOW)) {
      elbowServo.write(elbowServoSavedPos[i]);
    }
    delay(200);
    digitalWrite(activityLight, LOW);
  }
  else {
    digitalWrite(activityLight, LOW);
    digitalWrite(errorLight, HIGH);
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(safetyStopLight, HIGH);
    delay(200);
    digitalWrite(errorLight, LOW);
    digitalWrite(buzzerPin, LOW);
    baseServo.write(sPos1);
    pirSafetyVal = true;
    safetyStopVal = true;
  }
  
}

void loop() {
  basePotVal = analogRead(basePot);
  basePotAngle = map(basePotVal, 0, 1023, 0, 180);
  shoulderPotVal = analogRead(shoulderPot);
  shoulderPotAngle = map(shoulderPotVal, 0, 1023, 0, 180);
  elbowPotVal = analogRead(elbowPot);
  elbowPotAngle = map(elbowPotVal, 0, 1023, 0, 180);

  // Below runs the servos to the potentiometer positions
  baseServo.write(basePotAngle);
  shoulderServo.write(shoulderPotAngle);
  elbowServo.write(elbowPotAngle);

  // Check PIR
  if(digitalRead(pirPin)==LOW) {
    if(digitalRead(pirPin)==HIGH) {
      pirTriggers++;
      Serial.print('PIR Triggered');
      digitalWrite(errorLight, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(200);
      digitalWrite(errorLight, LOW);
      digitalWrite(buzzerPin, LOW);
    }
  }
//--------------------------------------------------------------------------------------------
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
        Serial.print('case 1');
        break;
      case 2:  // Saves potentiometer positions to servo angles memory 2
        baseServoSavedPos[1] = basePotAngle;
        shoulderServoSavedPos[1] = shoulderPotAngle;
        elbowServoSavedPos[1] = elbowPotAngle;
        Serial.print('case 2');
      break;
      case 3:  // Saves potentiometer positions to servo angles memory 3
        baseServoSavedPos[2] = basePotAngle;
        shoulderServoSavedPos[2] = shoulderPotAngle;
        elbowServoSavedPos[2] = elbowPotAngle;
        Serial.print('case 3');
      break;
      case 4:  // Saves potentiometer positions to servo angles memory 4
        baseServoSavedPos[3] = basePotAngle;
        shoulderServoSavedPos[3] = shoulderPotAngle;
        elbowServoSavedPos[3] = elbowPotAngle;
        Serial.print('case 4');
      break;
      case 5:  // Saves potentiometer positions to servo angles memory 5
        baseServoSavedPos[4] = basePotAngle;
        shoulderServoSavedPos[4] = shoulderPotAngle;
        elbowServoSavedPos[4] = elbowPotAngle;
        Serial.print('case 5');
      break;
    }
  }
  if(digitalRead(posRunButton) == HIGH) {
    posRunButtonIsPressed = true;
    Serial.print('pos Read');
  }

  if(posRunButtonIsPressed == true) {
    // Runs through memory positions
    // Checks safety of work environment, passes the first memory saved position as the initial position
    if(safetyStopVal == false) {
      for(int i = 0; i<5; i++) {  // Cycles through each memory position for servo
        // Moves each servo to it's ith memory position
        motorRun(baseServo.read(),i);  // Runs the motors
        Serial.print('Motor run ' + i);
        delay(1050);  // Stops robot operations for 1.5 secons)
      }
      posRunButtonIsPressed = false;
      posSaveButtonPresses = 0;
    }
  }
//-------------------------------------------------------------------------------------------- 
  while (pirSafetyVal == true) {  // Loop to check safety
    digitalWrite(safetyStopLight, HIGH);
    if(digitalRead(pirPin)==LOW) {
      delay(300);
      if(digitalRead(pirPin)==HIGH) {
        pirTriggers++;
        Serial.print('PIR Triggered');
        digitalWrite(errorLight, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(200);
        digitalWrite(errorLight, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(1000);
      }
      else {  // Subtract from PIR triggers
        pirTriggers--;
        Serial.print('Untriggered PIR');
        delay(1000);
      }
    if( pirTriggers <=0) {
      pirTriggers = 0;
      pirSafetyVal = false;
      }
    }
  }
  if (safetyStopVal == false) {  // Turns off safety light if value is false
    digitalWrite(safetyStopLight, LOW);
  }
  if(digitalRead(pirPin) == HIGH) {
    digitalWrite(safetyStopLight, HIGH);
    safetyStopVal = true;
    pirSafetyVal = true;
    delay(500);
    digitalWrite(safetyStopLight, LOW);
  }
  if(digitalRead(safetyButton) == HIGH) {
    // This function is a toggle for the safety stop button; toggles true or false
    switch(safetyStopVal){
     case false:
       safetyStopVal = true;
        digitalWrite(safetyStopLight, HIGH);
        digitalWrite(buzzerPin, HIGH);
        break;
     case true:
      safetyStopVal = false;
        digitalWrite(safetyStopLight, LOW);
        digitalWrite(buzzerPin, LOW);
        break;
    }
  }
  if(safetyStopVal == true) {  // Turns on safety light if value is true
   digitalWrite(safetyStopLight, HIGH); 
  }
  delay(300);  // Stops robot for 0.3 seconds
}
