#include <WiFi.h>
#include <WebSocketsServer.h>

// WiFi credentials
const char* SSID = "arnav";
const char* PASSWORD = "thisisArnav";

WebSocketsServer webSocket(81);

// Motor control pins
#define IN1 32  // Motor A Forward
#define IN2 25  // Motor A Reverse
#define ENA 33   // PWM for Motor A

#define IN3 27  // Motor B Forward
#define IN4 26  // Motor B Reverse
#define ENB 14  // PWM for Motor B

#define IN5 18  // Motor C Forward
#define IN6 19  // Motor C Reverse
#define ENC 23  // PWM for Motor C

#define IN7 21  // Motor D Forward
#define IN8 22  // Motor D Reverse
#define END 5  // PWM for Motor D

#define SPEED 255

void setup() {
    Serial.begin(115200);
    
    // Connect to WiFi
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.print("Connected! IP Address: ");
    Serial.println(WiFi.localIP());

    // Start WebSocket server
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);

    // Initialize motor pins
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
    webSocket.loop();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
        case WStype_TEXT: {
            String message = String((char*)payload);
            Serial.println("Received: " + message);
            stopAllMotors();
            
            if (message == "keydown:ArrowUp") {
                moveForward();
            } else if (message == "keydown:ArrowDown") {
                moveBackward();
            } else if (message == "keydown:ArrowLeft") {
                turnLeft();
            } else if (message == "keydown:ArrowRight") {
                turnRight();
            } else {
                stopAllMotors();
            }
            break;
        }
        case WStype_DISCONNECTED:
            Serial.printf("Client [%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED:
            Serial.printf("Client [%u] Connected!\n", num);
            break;
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
