#include <ESP32Servo.h>

// Define servo object
Servo myServo;

// Define servo pin
#define SERVO_PIN 18

// Define servo movement parameters
#define MIN_ANGLE 0
#define MAX_ANGLE 90
#define STEP_DELAY 20  // Delay in milliseconds

void setup() {
    myServo.attach(SERVO_PIN);
}

void loop() {
    // Move from 0° to 90°
    for (int angle = MIN_ANGLE; angle <= MAX_ANGLE; angle++) {
        myServo.write(angle);
        delay(STEP_DELAY);
    }

    // Move from 90° back to 0°
    for (int angle = MAX_ANGLE; angle >= MIN_ANGLE; angle--) {
        myServo.write(angle);
        delay(STEP_DELAY);
    }
}
