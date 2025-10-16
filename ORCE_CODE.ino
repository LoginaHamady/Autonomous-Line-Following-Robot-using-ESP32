// Define motor control pins 
#define ENA 21
#define IN1 19 
#define IN2 18 
#define IN3 5 
#define IN4 4 
#define ENB 2 

// Define sensor pins 
#define LEFTMOST_SENSOR 34  // Corner sensor
#define LEFTCENTER_SENSOR 35 
#define CENTER_SENSOR 32
#define RIGHTCENTER_SENSOR 33 
#define RIGHTMOST_SENSOR 25  // Corner sensor

#define STOP_DURATION 200  // Duration to stop before making a turn (in milliseconds)

int blackDetectionCounter = 0; // Counter to keep track of how many times all sensors read black 

void setup() { 
  // Set all the motor control pins to output 
  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT); 
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 

  // Set sensor pins to input 
  pinMode(LEFTMOST_SENSOR, INPUT); 
  pinMode(LEFTCENTER_SENSOR, INPUT); 
  pinMode(CENTER_SENSOR, INPUT); 
  pinMode(RIGHTCENTER_SENSOR, INPUT); 
  pinMode(RIGHTMOST_SENSOR, INPUT); 

  Serial.begin(9600); // Initialize serial communication for debugging 
} 

void loop() { 
  // Read sensor values 
  int leftmostSensorValue = digitalRead(LEFTMOST_SENSOR); 
  int leftcenterSensorValue = digitalRead(LEFTCENTER_SENSOR); 
  int centerSensorValue = digitalRead(CENTER_SENSOR); 
  int rightcenterSensorValue = digitalRead(RIGHTCENTER_SENSOR); 
  int rightmostSensorValue = digitalRead(RIGHTMOST_SENSOR); 

  // Print sensor values for debugging 
  Serial.print("LM: "); Serial.print(leftmostSensorValue);
  Serial.print(" LC: "); Serial.print(leftcenterSensorValue);
  Serial.print(" C: "); Serial.print(centerSensorValue);
  Serial.print(" RC: "); Serial.print(rightcenterSensorValue);
  Serial.print(" RM: "); Serial.println(rightmostSensorValue);

  // Check if all sensors are reading black
  if (leftmostSensorValue == 0 && leftcenterSensorValue == 0 &&
      centerSensorValue == 0 && rightcenterSensorValue == 0 &&
      rightmostSensorValue == 0) {
    blackDetectionCounter++;
    if (blackDetectionCounter == 1 || blackDetectionCounter == 2) {
      turnRight();
    } else if (blackDetectionCounter == 3) {
      turnLeft();
      blackDetectionCounter = 0;
    }
  } else {
    blackDetectionCounter = 0;

    // Handle sensor patterns
    if (leftmostSensorValue == 1 && leftcenterSensorValue == 0 &&
        centerSensorValue == 0 && rightcenterSensorValue == 0 &&
        rightmostSensorValue == 1) {
      moveForward(); // In Center
    } else if (leftmostSensorValue == 1 && leftcenterSensorValue == 1 &&
               centerSensorValue == 0 && rightcenterSensorValue == 1 &&
               rightmostSensorValue == 1) {
      moveForward(); // In center
    } else if (leftmostSensorValue == 1 && leftcenterSensorValue == 0 &&
               centerSensorValue == 0 && rightcenterSensorValue == 0 &&
               rightmostSensorValue == 0) {
      turnRight(); // Sharp Turn
    } else if (leftmostSensorValue == 0 && leftcenterSensorValue == 0 &&
               centerSensorValue == 0 && rightcenterSensorValue == 0 &&
               rightmostSensorValue == 1) {
      turnLeft(); // Sharp Turn
    } else if (leftmostSensorValue == 0 && leftcenterSensorValue == 0 &&
               centerSensorValue == 1 && rightcenterSensorValue == 0 &&
               rightmostSensorValue == 1) {
      slightMoveForward();
    } else if (leftmostSensorValue == 0 && leftcenterSensorValue == 1 &&
               centerSensorValue == 0 && rightcenterSensorValue == 0 &&
               rightmostSensorValue == 1) {
      slightMoveForward();
    } else if (leftmostSensorValue == 1 && leftcenterSensorValue == 1 &&
               centerSensorValue == 0 && rightcenterSensorValue == 0 &&
               rightmostSensorValue == 1) {
      slightTurnRight();
    } else if (leftmostSensorValue == 0 && leftcenterSensorValue == 0 &&
               centerSensorValue == 1 && rightcenterSensorValue == 1 &&
               rightmostSensorValue == 0) {
      slightTurnLeft();
    } else if (leftmostSensorValue == 1 && leftcenterSensorValue == 0 &&
               centerSensorValue == 1 && rightcenterSensorValue == 0 &&
               rightmostSensorValue == 1) {
      slightMoveForward();
    } else if (leftmostSensorValue == 1 && leftcenterSensorValue == 1 &&
               centerSensorValue == 1 && rightcenterSensorValue == 0 &&
               rightmostSensorValue == 1) {
      slightTurnRight();
    } else if (leftmostSensorValue == 1 && leftcenterSensorValue == 1 &&
               centerSensorValue == 1 && rightcenterSensorValue == 1 &&
               rightmostSensorValue == 1) {
      slightMoveForward(); // White gaps
    } else if (leftmostSensorValue == 1 && leftcenterSensorValue == 1 &&
               centerSensorValue == 0 && rightcenterSensorValue == 0 &&
               rightmostSensorValue == 0) {
      turnRight();
    } else if (leftmostSensorValue == 0 && leftcenterSensorValue == 1 &&
               centerSensorValue == 1 && rightcenterSensorValue == 0 &&
               rightmostSensorValue == 0) {
      slightTurnRight();
    } else if (leftmostSensorValue == 1 && leftcenterSensorValue == 0 &&
               centerSensorValue == 1 && rightcenterSensorValue == 1 &&
               rightmostSensorValue == 1) {
      slightTurnLeft();
    } else if (leftmostSensorValue == 1 && leftcenterSensorValue == 0 &&
               centerSensorValue == 1 && rightcenterSensorValue == 1 &&
               rightmostSensorValue == 0) {
      slightMoveForward();
    } else if (leftmostSensorValue == 0 && leftcenterSensorValue == 0 &&
               centerSensorValue == 1 && rightcenterSensorValue == 1 &&
               rightmostSensorValue == 1) {
      turnLeft();
    } else if (leftmostSensorValue == 1 && leftcenterSensorValue == 1 &&
               centerSensorValue == 1 && rightcenterSensorValue == 0 &&
               rightmostSensorValue == 0) {
      turnRight();
    } else if (leftmostSensorValue == 1 && leftcenterSensorValue == 1 &&
               centerSensorValue == 1 && rightcenterSensorValue == 1 &&
               rightmostSensorValue == 0) {
      turnRight();
    } else if (leftmostSensorValue == 0 && leftcenterSensorValue == 1 &&
               centerSensorValue == 1 && rightcenterSensorValue == 0 &&
               rightmostSensorValue == 1) {
      slightMoveForward();
    } else if (leftmostSensorValue == 1 && leftcenterSensorValue == 1 &&
               centerSensorValue == 0 && rightcenterSensorValue == 1 &&
               rightmostSensorValue == 0) {
      slightMoveForward();
    } else if (leftmostSensorValue == 1 && leftcenterSensorValue == 0 &&
               centerSensorValue == 0 && rightcenterSensorValue == 1 &&
               rightmostSensorValue == 1) {
      slightTurnLeft();
    } else if (leftmostSensorValue == 0 && leftcenterSensorValue == 1 &&
               centerSensorValue == 0 && rightcenterSensorValue == 1 &&
               rightmostSensorValue == 1) {
      slightMoveForward();
    } else {
      stopMotors();
    }
  }
  delay(20); // Delay for sensor stability
}

void moveForward() { 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);   // Forward motion for motor A 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);   // Forward motion for motor B 
  analogWrite(ENA, 150);    // Set speed 
  analogWrite(ENB, 150);    // Set speed 
} 

void slightMoveForward() { 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);   // Forward motion for motor A 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);   // Forward motion for motor B 
  analogWrite(ENA, 100);    // Set speed 
  analogWrite(ENB, 100);    // Set speed 
} 

void slightTurnRight() { 
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);    // Reverse motion for motor A 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);   // Forward motion for motor B 
  analogWrite(ENA, 100);    // Set speed 
  analogWrite(ENB, 100);    // Set speed 
} 

void slightTurnLeft() { 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);   // Forward motion for motor A 
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);    // Reverse motion for motor B 
  analogWrite(ENA, 100);    // Set speed 
  analogWrite(ENB, 100);    // Set speed 
} 

void turnRight() { 
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);    // Reverse motion for motor A 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);   // Forward motion for motor B 
  analogWrite(ENA, 150);    // Set speed 
  analogWrite(ENB, 150);    // Set speed 
} 

void turnLeft() { 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);   // Forward motion for motor A 
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);    // Reverse motion for motor B 
  analogWrite(ENA, 150);    // Set speed 
  analogWrite(ENB, 150);    // Set speed 
} 

void stopMotors() { 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW);   // Stop motor A 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW);   // Stop motor B 
  analogWrite(ENA, 0);     // Stop motor A 
  analogWrite(ENB, 0);     // Stop motor B 
} 
