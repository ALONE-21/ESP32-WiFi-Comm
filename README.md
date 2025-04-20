
# ESP32 ESP-NOW Transceiver

This project enables **bidirectional communication** (transmitting and receiving) between two ESP32 devices using **ESP-NOW** — a fast and connectionless communication protocol. You can send messages from one ESP32 to another by typing them in the Serial Monitor.

## 🚀 Features

- Acts as both **sender** and **receiver** (transceiver)
- No need for Wi-Fi connection or internet
- Fast, low-latency peer-to-peer communication
- Simple Serial interface for sending and viewing messages
- Prints MAC address of sender for received messages

## 🔧 Hardware Required

- Two ESP32 development boards (e.g., NodeMCU-ESP32, DevKit v1)
- USB cables and Arduino IDE

## 📦 How It Works

- Type a message in the Serial Monitor of one ESP32
- The message is sent to the other ESP32 using ESP-NOW
- The receiving ESP32 displays the message along with the sender's MAC address

## 📁 Code Overview

The sketch does the following:

1. Initializes Wi-Fi in `WIFI_STA` mode
2. Sets up ESP-NOW
3. Registers the peer device using its MAC address
4. Sends and receives messages as `struct_message` (a simple structure with a text field)

## 🔁 Setup Instructions

1. Clone this repository or download the `.ino` file
2. Open in Arduino IDE
3. Install the required board support for **ESP32** (via Board Manager)
4. Connect both ESP32 boards to your PC
5. Upload the same code to both boards, but **change the `peerAddress[]`** to match the **MAC address of the other board**

### 🔍 Finding the MAC Address

Upload the following code to an ESP32 to get its MAC address:

```cpp
#include <WiFi.h>
void setup() {
  Serial.begin(115200);
  Serial.println(WiFi.macAddress());
}
void loop() {}
```

Copy the output and paste it into the `peerAddress[]` array in the main code.

## 🧪 Example Output

On one ESP32:
```
✅ Transceiver ready. Type a message and press Enter to send.
📤 Sent: Hello, ESP32 B!
```

On the other ESP32:
```
📥 Received from 78:42:1C:6C:BB:1C: Hello, ESP32 B!
```

## ✅ Dependencies

- ESP32 Arduino Core
- No external libraries required (uses built-in `WiFi` and `esp_now`)

## 📄 License

This project is licensed under the MIT License — feel free to use, modify, and share!

---

### 🧠 Author Notes

This project was built to test and demonstrate ESP-NOW's potential for peer-to-peer communication. It can be extended to support sensors, control systems, or even lightweight chat between ESPs.

Happy tinkering! 🤖
