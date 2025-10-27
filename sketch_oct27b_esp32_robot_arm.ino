#include <WiFi.h>
#include <ESP32Servo.h>

// === Wi-Fi Setup ===
const char* ssid = "HS";
const char* password = "2025@#$%1";

// === Servo Setup ===
Servo servoBase;
Servo servoShoulder;

int basePos = 90;
int shoulderPos = 90;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  servoBase.attach(26);
  servoShoulder.attach(27);  // <<--- SHOULDER pin (change if needed)

  servoBase.write(basePos);
  servoShoulder.write(shoulderPos);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String req = client.readStringUntil('\r');
  client.flush();
  Serial.println(req);

  if (req.indexOf("base=") != -1) {
    basePos = getValue(req, "base");
    basePos = constrain(basePos, 0, 180);
    servoBase.write(basePos);
    Serial.print("Base = ");
    Serial.println(basePos);
  }

  if (req.indexOf("shoulder=") != -1) {
    shoulderPos = getValue(req, "shoulder");
    shoulderPos = constrain(shoulderPos, 0, 180);
    servoShoulder.write(shoulderPos);
    Serial.print("Shoulder = ");
    Serial.println(shoulderPos);
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println("<!DOCTYPE html><html>");
  client.println("<h2>Robot Arm Control</h2>");

  // BASE
  client.println("<p><b>Base:</b></p>");
  client.println("<input type='range' min='0' max='180' value='" + String(basePos) + "' oninput='send(\"base\",this.value)'><br><br>");

  // SHOULDER
  client.println("<p><b>Shoulder:</b></p>");
  client.println("<input type='range' min='0' max='180' value='" + String(shoulderPos) + "' oninput='send(\"shoulder\",this.value)'><br><br>");

  client.println("<script>");
  client.println("function send(name,val){fetch('/?'+name+'='+val).catch(()=>{});}");  
  client.println("</script>");

  client.println("</html>");
  client.stop();
}

int getValue(String req, String name) {
  int s = req.indexOf(name + "=") + name.length() + 1;
  int e = req.indexOf(' ', s);
  if (e == -1) e = req.length();
  return req.substring(s, e).toInt();
}
