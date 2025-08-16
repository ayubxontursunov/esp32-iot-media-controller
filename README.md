# 📡 ESP32 IoT Media Controller

## 🌟 Project Overview
This project was developed during my internship at **MakTech** as an **Embedded Software Engineer** (03/2025 – 06/2025).  
The goal was to design and implement an **ESP32-based IoT media controller** capable of streaming videos and images from a remote server to a fullscreen browser display.

The system supports **multiple input methods**:
- 🌐 **Web Interface** (AsyncWebServer + Server-Sent Events)  
- 🎛️ **Physical Buttons** (GPIO 16, 17, 18)  
- 💻 **Serial Commands**

---

## 🔑 Features
- ESP32-powered IoT device with Wi-Fi connectivity  
- Async Web Server serving a browser-based UI  
- Real-time updates via **Server-Sent Events (SSE)**  
- Multi-input control:
  - GPIO buttons
  - Serial monitor
  - Web UI (auto fullscreen media display)  
- Supports **images & videos** (looping, fullscreen)  
- Button **debouncing logic** for reliable inputs  
- Integration with external Python server for media hosting  

---

## 🖥️ Technology Stack
- **Hardware:** ESP32  
- **Languages:** C++ (Arduino), HTML, JavaScript  
- **Libraries:** `WiFi.h`, `ESPAsyncWebServer.h`  
- **Networking:** Wi-Fi (802.11), HTTP, SSE  
- **Media Hosting:** Python HTTP Server  

---

## ⚙️ Hardware Setup
- ESP32 Dev Board  
- Push buttons connected to **GPIO 16, 17, 18** with `INPUT_PULLUP`  
- External server hosting media files (`video1.mp4`, `video2.mp4`, `image.jpg`)  

### Button Mapping
- **BTN1 (GPIO16)** → Play Video 1  
- **BTN2 (GPIO17)** → Play Video 2  
- **BTN3 (GPIO18)** → Show Image  

---

## 🚀 How It Works
1. ESP32 connects to Wi-Fi and launches an **Async Web Server**  
2. Browser clients connect → receive fullscreen media UI  
3. Initial media is fetched from `/getMedia`  
4. **Server-Sent Events** update clients instantly when media changes  
5. Media can be switched via:
   - 🔹 Serial commands (`1`, `2`, `3`)  
   - 🔹 Button presses (BTN1, BTN2, BTN3)  
   - 🔹 Web UI  

---

## 📄 Documentation
In addition to coding, I created a **research report** on **IoT power solutions**, covering:
- Low-power microcontrollers (ESP32)  
- Wireless communication (Wi-Fi, BLE, LoRa)  
- Battery technologies (Li-ion, LiPo, LiFePO4)  
- **Wireless charging** (Qi modules)  
- **Thin wire charging** for higher power needs  
- Circuit diagrams & implementation guidelines  

📄 File: *IoT_Power_Solutions.docx*  

---

## 🏆 My Role
As an **Embedded IoT Engineer Intern** at MakTech, I:
- Developed an **ESP32-based IoT media controller**  
- Implemented **real-time browser updates** with SSE  
- Enabled **multi-input media control** (buttons, serial, web)  
- Authored **technical documentation** on IoT power solutions  

---

## 📌 Future Improvements
- Add MQTT for cloud integration  
- Multi-device sync playback  
- OTA firmware updates  
- Portable design with **wireless charging**  

---

✨ This project showcases my skills in **embedded systems, IoT solutions, real-time communication, and documentation**.
