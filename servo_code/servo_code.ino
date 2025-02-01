#include <ESP32Servo.h>

#define IN1 2
#define IN2 4

Servo myServo1;
Servo myServo2;

void setup() {
    myServo1.attach(IN1);
    myServo2.attach(IN2);
}

void loop() {
    writeAngle(0);
}

void writeAngle(int n) {
    myServo1.write(n);
    myServo2.write(90 - n);
}