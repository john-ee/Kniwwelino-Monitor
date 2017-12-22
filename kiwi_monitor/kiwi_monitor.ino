#include <Kniwwelino.h>
#include <KniwwelinoIcons.h>

uint8_t brightness = 10;

const char *ssid = "Dom";
const char *password = "offm1prop3rt1";
IPAddress myIP(192,168,1,2);
IPAddress gw(192,168,1,1);
IPAddress mask(255,255,255,0);


void setup() {
  Kniwwelino.begin(false, true);

  Serial.begin(115200);

  Kniwwelino.RGBsetBrightness(brightness);

  //WiFi.softAPConfig(myIP, gw, mask);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.println("Connecting..");
    Kniwwelino.RGBsetColorEffect(RGB_COLOR_RED, RGB_FLASH, -1);
  }

  Serial.println(WiFi.localIP());
  Kniwwelino.RGBsetColorEffect(RGB_COLOR_GREEN, RGB_FLASH, -1);
}

void loop() {

  while (WiFi.status() != WL_CONNECTED) {

    if (Kniwwelino.BUTTONAclicked()) {
      Kniwwelino.RGBsetColorEffect(RGB_COLOR_BLUE, RGB_FLASH, -1);
      HTTPClient http;
      http.begin("http://192.168.1.1/temperature");
      int httpCode = http.GET();
      Serial.println("send req");
      Serial.println(httpCode);

      if (httpCode > 0) {
        Kniwwelino.RGBsetColorEffect(RGB_COLOR_GREEN, RGB_FLASH, -1);
        String payload = http.getString();
        Kniwwelino.MATRIXwriteOnce(payload);
        Serial.println(payload);
      }

      http.end();
    }
  }
  Kniwwelino.RGBsetColorEffect(RGB_COLOR_RED, RGB_FLASH, -1);
  Kniwwelino.sleep(100);
}
