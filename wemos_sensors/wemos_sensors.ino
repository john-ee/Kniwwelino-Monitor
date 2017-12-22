#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Dom";
const char *password = "offm1prop3rt1";
IPAddress hostIP(192,168,1,1);
IPAddress gw(192,168,1,1);
IPAddress mask(255,255,255,0);

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

void serveTemperature() {
  int randomNumber = random(15,35);
  server.send(200, "text/plain", String(randomNumber));
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  Serial.print("Configuring access point...");
  WiFi.softAPConfig(hostIP, gw, mask);
  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(hostIP);

  server.on("/", handleRoot);
  server.on("/temperature", serveTemperature);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
