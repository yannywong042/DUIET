//*********************************************
// Time-Series Signal Processing
// Rong-Hao Liang: r.liang@tue.nl
//*********************************************
#include <Servo.h> 

Servo myServo;

int sampleRate = 100; //samples per second
int sampleInterval = 500000/sampleRate; //Inverse of SampleRate
long timer = micros(); //timer

int dtServo = 0; 

void setup() {
  Serial.begin(115200); //serial
  myServo.attach(9);      
  myServo.write(0);
}

void loop() {
  if (micros() - timer >= sampleInterval) { //Timer: send sensor data in every 10ms
    timer = micros();
    getDataFromProcessing(); //Receive before sending out the signals
  }
}

void getDataFromProcessing() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == 'a') { //when an 'a' character is received.
      dtServo = 1;
      myServo.write(90);
    }
    if (inChar == 'b') { //when an 'b' character is received.
      dtServo = 0;
      myServo.write(0);
    }
  }
}
