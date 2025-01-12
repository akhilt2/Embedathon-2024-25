#include <WiFi.h>
#include <WebSocketsServer.h>
#include <Preferences.h>
#include <base64.h>

const char* apSSID = "ESP32_AP";
const char* apPassword = "12345678";

WebSocketsServer webSocket = WebSocketsServer(81);
Preferences preferences;
String extractedMessage = "";

void extractMessageFromNVM() {
  if (!preferences.begin("Passwords", false)) {
    Serial.println("Failed to open namespace 'Passwords'");
    return;
  }

  for (int i = 0; i <= 6; i++) {
    String key = "line" + String(i);
    String line = preferences.getString(key.c_str(), "");
    if (line != "") {
      extractedMessage += line;
      extractedMessage += "\n";
    }
  }

  preferences.end();
  Serial.println("Message extracted from NVM:");
  Serial.println(extractedMessage);
}

void onWebSocketEvent(uint8_t clientNum, WStype_t type, uint8_t* payload, size_t length) {
  if (type == WStype_CONNECTED) {
    Serial.printf("Client [%u] connected!\n", clientNum);
    String encodedMessage = base64::encode(extractedMessage);
    webSocket.sendTXT(clientNum, encodedMessage);
  }
}

void setup() {
  Serial.begin(115200);

  Serial.println("Starting Wi-Fi Access Point...");
  WiFi.softAP(apSSID, apPassword);

  IPAddress IP = WiFi.softAPIP();
  Serial.println("Access Point started.");
  Serial.print("IP Address: ");
  Serial.println(IP);

  extractMessageFromNVM();

  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
  Serial.println("WebSocket server started.");
}

void loop() {
  webSocket.loop();
}
