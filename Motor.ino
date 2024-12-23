//*********************************************
// Time-Series Signal Processing
// Rong-Hao Liang: r.liang@tue.nl
//*********************************************
#include <L298N.h>

// Pin definitions for Motor A
const unsigned int IN1_A = 5;
const unsigned int IN2_A = 4;
const unsigned int EN_A = 3;

// Pin definitions for Motor B
const unsigned int IN1_B = 7;
const unsigned int IN2_B = 6;
const unsigned int EN_B = 9;

// Create motor instances
L298N motorA(EN_A, IN1_A, IN2_A);
L298N motorB(EN_B, IN1_B, IN2_B);

int sampleRate = 100;                      //samples per second
int sampleInterval = 500000 / sampleRate;  //Inverse of SampleRate
long timer = micros();                     //timer

int dtServo = 0;

void setup() {
  Serial.begin(9600);  //serial
  // Wait for Serial Monitor to be opened
  while (!Serial) {
    // Do nothing
  }
  // Set initial speed for both motors
  motorA.setSpeed(100);
  motorB.setSpeed(100);
}

void loop() {
  if (micros() - timer >= sampleInterval) {  //Timer: send sensor data in every 10ms
    timer = micros();
    getDataFromProcessing();  //Receive before sending out the signals
  }
}

void getDataFromProcessing() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == 'a') {  //when an 'a' character is received.
      dtServo = 1;
      motorA.backward();
      motorB.forward();

      // Print motor status
      Serial.println("Motor A: Backward, Motor B: Forward");

      delay(10000);  // Run for 10 seconds

      // Stop both motors
      motorA.stop();
      motorB.stop();

      Serial.println("Motors stopped");
    }
    if (inChar == 'b') {  //when an 'b' character is received.
      dtServo = 0;
      motorA.stop();
      motorB.stop();
    }
  }
}
