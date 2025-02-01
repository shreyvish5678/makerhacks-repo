#define IN1 18  // Motor A Forward
#define IN2 19  // Motor A Reverse
#define IN3 21  // Motor B Forward
#define IN4 22  // Motor B Reverse
#define IN5 18  // Motor C Forward
#define IN6 19  // Motor C Reverse
#define IN7 21  // Motor D Forward
#define IN8 22  // Motor D Reverse
#define ENA 5   // PWM for Motor A
#define ENB 15  // PWM for Motor B
#define ENC 25  // PWM for Motor C
#define END 26  // PWM for Motor D
#define SPEED 255 // Speed for the motors (0-255)

char command; 

void setup() {
    Serial.begin(9600);  // Start serial communication at 9600 baud rate

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT); 
    pinMode(ENB, OUTPUT);
    pinMode(IN5, OUTPUT);
    pinMode(IN6, OUTPUT);
    pinMode(IN7, OUTPUT);
    pinMode(IN8, OUTPUT);
    pinMode(ENC, OUTPUT);
    pinMode(END, OUTPUT);
}

void loop() {
    if (Serial.available() > 0) {
        command = Serial.read();  // Read the incoming byte
        stopAllMotors();  // Initialize with motors stopped
        
        switch (command) {
            case 'F':  
                moveForward();
                break;
            case 'B':  
                moveBackward();
                break;
            case 'L':  
                turnLeft();
                break;
            case 'R':  
                turnRight();
                break;
        }
    }
}

void moveForward() {
    driveAllForward(SPEED);
}

void moveBackward() {
    driveAllBackward(SPEED);
}

void turnLeft() {
    rotateLeft(SPEED);
}

void turnRight() {
    rotateRight(SPEED);
}

void stopAllMotors() {
    stopMotor(IN1, IN2);
    stopMotor(IN3, IN4);
    stopMotor(IN5, IN6);
    stopMotor(IN7, IN8);
}

void stopMotor(int pin1, int pin2) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
}

void setMotorSpeed(int speed) {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    analogWrite(ENC, speed);
    analogWrite(END, speed);
}

void driveForward(int pin1, int pin2) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
}

void driveBackward(int pin1, int pin2) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
}

void driveAllForward(int speed) {
    setMotorSpeed(speed);
    driveForward(IN1, IN2);
    driveForward(IN3, IN4);
    driveForward(IN5, IN6);
    driveForward(IN7, IN8);
}

void driveAllBackward(int speed) {
    setMotorSpeed(speed);
    driveBackward(IN1, IN2);
    driveBackward(IN3, IN4);
    driveBackward(IN5, IN6);
    driveBackward(IN7, IN8);
}

void rotateRight(int speed) {
    setMotorSpeed(speed);
    driveForward(IN1, IN2);
    driveBackward(IN3, IN4);
    driveForward(IN5, IN6);
    driveBackward(IN7, IN8);
}

void rotateLeft(int speed) {
    setMotorSpeed(speed);
    driveBackward(IN1, IN2);
    driveForward(IN3, IN4);
    driveBackward(IN5, IN6);
    driveForward(IN7, IN8);
}