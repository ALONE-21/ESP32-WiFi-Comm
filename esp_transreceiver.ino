#include <WiFi.h>
#include <esp_now.h>

// ⚠️ Replace this with the OTHER ESP32's MAC address 0xXX is a hexadecimal format replace only XX
uint8_t peerAddress[] = {0xAA, 0xAA, 0xAA 0xAA, 0xBB, 0x1C};

// Structure to send/receive messages
typedef struct struct_message {
  char text[250];
} struct_message;

struct_message incomingData;
struct_message outgoingData;

String inputBuffer = "";

void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  memcpy(&incomingData, data, sizeof(incomingData));
  Serial.print("\n📥 Received from ");
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           info->src_addr[0], info->src_addr[1], info->src_addr[2],
           info->src_addr[3], info->src_addr[4], info->src_addr[5]);
  Serial.print(macStr);
  Serial.print(": ");
  Serial.println(incomingData.text);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (!esp_now_is_peer_exist(peerAddress)) {
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      Serial.println("Failed to add peer");
      return;
    }
  }

  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("✅ Transceiver ready. Type a message and press Enter to send.");
}

void loop() {
  if (Serial.available()) {
    inputBuffer = Serial.readStringUntil('\n');
    inputBuffer.trim();
    if (inputBuffer.length() > 0) {
      inputBuffer.toCharArray(outgoingData.text, sizeof(outgoingData.text));
      esp_err_t result = esp_now_send(peerAddress, (uint8_t *)&outgoingData, sizeof(outgoingData));

      if (result == ESP_OK) {
        Serial.print("📤 Sent: ");
        Serial.println(outgoingData.text);
      } else {
        Serial.println("❌ Send failed");
      }
    }
  }
}
