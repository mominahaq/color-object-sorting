
#include <Servo.h>

// ---------------- PIN ASSIGNMENTS ----------------

// Sensors
#define IR_PIN 2              // IR object detection (LOW = object present)
#define METAL_PIN 3           // Inductive metal sensor (HIGH = metal detected)

// TCS3200 Color Sensor
#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define SENSOR_OUT 12

// L298N Motor Driver for Conveyor
#define ENA 5                 // PWM speed control
#define IN1 6
#define IN2 7

// Servos for sorting bins (Option B)
Servo servoMetalRed;          // Bin 1: Metal + Red
Servo servoMetalBlue;         // Bin 2: Metal + Blue
Servo servoNonMetalRed;       // Bin 3: Non-Metal + Red
Servo servoNonMetalBlue;      // Bin 4: Non-Metal + Blue

// Servo pins
#define SERVO_METAL_RED_PIN      4
#define SERVO_METAL_BLUE_PIN     A0
#define SERVO_NONMETAL_RED_PIN   A1
#define SERVO_NONMETAL_BLUE_PIN  A2

// Color reading variables
int redVal, greenVal, blueVal;

// ----------------------------------------------------------
// INITIAL SETUP
// ----------------------------------------------------------
void setup() {
  Serial.begin(9600);

  pinMode(IR_PIN, INPUT);
  pinMode(METAL_PIN, INPUT);

  // Conveyor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // TCS3200 configuration
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SENSOR_OUT, INPUT);

  // TCS3200 frequency scaling
  digitalWrite(S0, HIGH);     // S0 = 1
  digitalWrite(S1, LOW);      // S1 = 0 -> 20% frequency scaling

  // Attach servos
  servoMetalRed.attach(SERVO_METAL_RED_PIN);
  servoMetalBlue.attach(SERVO_METAL_BLUE_PIN);
  servoNonMetalRed.attach(SERVO_NONMETAL_RED_PIN);
  servoNonMetalBlue.attach(SERVO_NONMETAL_BLUE_PIN);

  // Initialize
  resetServos();
  startConveyor();
  Serial.println("System Ready...");
}

// ----------------------------------------------------------
// MAIN LOOP
// ----------------------------------------------------------
void loop() {

  // Object detected?
  if (digitalRead(IR_PIN) == LOW) {
    Serial.println("Object detected!");
    stopConveyor();
    delay(300);

    // Check metal or non-metal
    bool isMetal = digitalRead(METAL_PIN);
    Serial.print("Metal Sensor: ");
    Serial.println(isMetal ? "METAL" : "NON-METAL");

    // Read object color
    readColor();

    // Decide RED / BLUE
    bool isRed = (redVal < blueVal);

    // ---------------- SORTING LOGIC (OPTION B) ----------------
    if (isMetal && isRed) {
      Serial.println("=> Sorting to Bin 1 (Metal + Red)");
      servoMetalRed.write(90);

    } else if (isMetal && !isRed) {
      Serial.println("=> Sorting to Bin 2 (Metal + Blue)");
      servoMetalBlue.write(90);

    } else if (!isMetal && isRed) {
      Serial.println("=> Sorting to Bin 3 (Non-Metal + Red)");
      servoNonMetalRed.write(90);

    } else {
      Serial.println("=> Sorting to Bin 4 (Non-Metal + Blue)");
      servoNonMetalBlue.write(90);
    }

    delay(700);     // Wait for servo action
    resetServos();  // Return servos to home position
    startConveyor();
  }
}

// ----------------------------------------------------------
// READ COLOR FROM TCS3200
// ----------------------------------------------------------
void readColor() {

  // READ RED
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redVal = pulseIn(SENSOR_OUT, LOW);

  // READ BLUE
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  blueVal = pulseIn(SENSOR_OUT, LOW);

  // READ GREEN (optional, not used in decision)
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  greenVal = pulseIn(SENSOR_OUT, LOW);

  // Print color data
  Serial.print("Color => R:");
  Serial.print(redVal);
  Serial.print(" G:");
  Serial.print(greenVal);
  Serial.print(" B:");
  Serial.println(blueVal);
}

// ----------------------------------------------------------
// RESET SERVOS TO HOME POSITION
// ----------------------------------------------------------
void resetServos() {
  servoMetalRed.write(0);
  servoMetalBlue.write(0);
  servoNonMetalRed.write(0);
  servoNonMetalBlue.write(0);
}

// ----------------------------------------------------------
// CONVEYOR MOTOR CONTROL
// ----------------------------------------------------------
void startConveyor() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 180);   // speed control (0-255)
}

void stopConveyor() {
  analogWrite(ENA, 0);
}
