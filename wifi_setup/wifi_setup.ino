#include <WiFi.h>
#include <WebSocketsServer.h>

// WiFi credentials
const char* SSID = "YourWiFiSSID";
const char* PASSWORD = "YourWiFiPassword";

WebSocketsServer webSocket(81); // WebSocket server on port 81
String lastKeyState = ""; // Stores the last key state

// WebSocket event handler
void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
        case WStype_TEXT: {
            String message = String((char*)payload);
            Serial.println("Received: " + message);
            
            // Example: Control motors based on received key events
            if (message == "keydown:ArrowUp") {
                Serial.println("Moving Forward");
            } else if (message == "keydown:ArrowDown") {
                Serial.println("Moving Backward");
            } else if (message == "keydown:ArrowLeft") {
                Serial.println("Turning Left");
            } else if (message == "keydown:ArrowRight") {
                Serial.println("Turning Right");
            } else if (message.startsWith("keyup:")) {
                Serial.println("Stopping Motion");
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
}

void loop() {
    webSocket.loop();
}