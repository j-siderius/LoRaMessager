#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "AsyncTCP.h"
#include "SPIFFS.h"

const char* ssid = "LoRaMessenger";
String message;
IPAddress local_IP(192, 168, 0, 1);
IPAddress gateway(192, 168, 0, 0);
IPAddress subnet(255, 255, 255, 0);

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.softAPConfig(local_IP, gateway, subnet);
  if (!WiFi.softAP(ssid)) {
    Serial.println("An Error has occured while starting the AP");
    }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });

  server.on("/m", HTTP_GET, [] (AsyncWebServerRequest * request) {
    if (request->hasParam("message")) {
      message = request->getParam("message")->value();
      request->send(200, "text/html", "Your message has been sent!:\n"
                    + message + "<br><a href=\"/\">Return to Home Page</a>");
      Serial.print("Message received: "); Serial.println(message);
    } else {
      request->send(404, "text/plain", "Not found");
    }
  });
  
  server.begin();
}

void loop() {

}
