#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define BTN1 16
#define BTN2 17
#define BTN3 18


const char* ssid = "your hotspot";         // Your hotspot SSID
const char* password = "your hostpot password";    // Your hotspot password

// REMOVE THIS STATIC CONFIG — it causes IP conflict if subnet doesn't match
// IPAddress local_IP(192, 168, 1, 184);
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 255, 0);

AsyncWebServer server(80);
AsyncEventSource events("/events");

// Media URLs (hosted on your PC using Python HTTP server)
String media1 = "http://172.20.240.1:8000/video1.mp4";
String media2 = "http://172.20.240.1:8000/video2.mp4";
String media3 = "http://172.20.240.1:8000/image.jpg";

String currentMedia = media3;
bool isVideo = false;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <script>
    let fullscreenActivated = false;

    function activateFullscreen() {
      if (fullscreenActivated) return;
      fullscreenActivated = true;
      if (document.documentElement.requestFullscreen) {
        document.documentElement.requestFullscreen().catch(err => console.warn("Fullscreen failed:", err));
      }
    }

    function displayMedia(data) {
      const mediaDiv = document.getElementById("media");
      mediaDiv.innerHTML = "";

      if (data.isVideo) {
        const video = document.createElement('video');
        video.setAttribute('autoplay', '');
        video.setAttribute('muted', '');
        video.setAttribute('playsinline', '');
        video.setAttribute('loop', '');
        video.style.width = '100vw';
        video.style.height = '100vh';
        video.style.objectFit = 'cover';

        const source = document.createElement('source');
        source.setAttribute('src', data.url);
        source.setAttribute('type', 'video/mp4');

        video.appendChild(source);
        mediaDiv.appendChild(video);
      } else {
        const img = document.createElement('img');
        img.setAttribute('src', data.url);
        img.style.width = '100vw';
        img.style.height = '100vh';
        img.style.objectFit = 'cover';
        mediaDiv.appendChild(img);
      }
    }

    window.onload = () => {
      activateFullscreen();

      fetch('/getMedia')
        .then(response => response.json())
        .then(data => {
          displayMedia(data);
        });

      const evtSource = new EventSource("/events");
      evtSource.onmessage = (event) => {
        const data = JSON.parse(event.data);
        displayMedia(data);
      };
    };
  </script>
</head>
<body style="margin:0; overflow:hidden; background:black;">
  <div id="media" style="width:100vw; height:100vh;"></div>
</body>
</html>
)rawliteral";

void handleGetMedia(AsyncWebServerRequest *request) {
  String json = "{\"url\":\"" + currentMedia + "\", \"isVideo\":" + (isVideo ? "true" : "false") + "}";
  request->send(200, "application/json", json);
}

void updateMedia(String url, bool videoFlag) {
  currentMedia = url;
  isVideo = videoFlag;
  String json = "{\"url\":\"" + currentMedia + "\", \"isVideo\":" + (isVideo ? "true" : "false") + "}";
  events.send(json.c_str(), "message", millis());
  Serial.println("Media updated: " + url);
}

void setup() {
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);

  Serial.begin(115200);

  // REMOVE STATIC IP (this was causing connection issues)
  // if (!WiFi.config(local_IP, gateway, subnet)) {
  //   Serial.println("STA Failed to configure");
  // }

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());  // Use this IP in browser

  Serial.println("Send:");
  Serial.println("1 - Play Video1");
  Serial.println("2 - Play Video2");
  Serial.println("3 - Show Image");

  // Handle root page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", index_html);
  });

  server.on("/getMedia", HTTP_GET, handleGetMedia);
  server.addHandler(&events);
  server.begin();

  delay(1000);  // Give time for browser to connect
  updateMedia(currentMedia, isVideo);
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == '1') updateMedia(media1, true);
    else if (cmd == '2') updateMedia(media2, true);
    else if (cmd == '3') updateMedia(media3, false);
  }

  static unsigned long lastPress = 0;
  if (millis() - lastPress > 300) {
    if (digitalRead(BTN1) == LOW) {
      updateMedia(media1, true);
      lastPress = millis();
    } else if (digitalRead(BTN2) == LOW) {
      updateMedia(media2, true);
      lastPress = millis();
    } else if (digitalRead(BTN3) == LOW) {
      updateMedia(media3, false);
      lastPress = millis();
    }
  }
}
