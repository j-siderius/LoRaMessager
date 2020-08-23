#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "AsyncTCP.h"
#include "DNSServer.h"
#include "SPIFFS.h"
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  868E6


const char* ssid = "LoRaMessenger";
const uint8_t phoneNumber;
IPAddress local_IP(192, 168, 1, 0);
IPAddress gateway(10, 1, 1, 1);
IPAddress subnet(255, 255, 255, 0);

DNSServer dnsServer;
AsyncWebServer server(80);

String message;
void urlDefine(){}

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n\n----------------------------------------");
  Serial.println("LoRaWebserverTest2");

  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("Lora started");
  phoneNumber = random(10000000,100000000);
  Serial.print("Phonenumber: "); Serial.println(phoneNumber);

  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  Serial.println("SPIFFS mounted");

  ssid += random(1000,10000);
  if (!WiFi.softAP(ssid)) {
    Serial.println("An Error has occured while starting the AP");
  }
  Serial.print("AP started: "); Serial.println(ssid);
  delay(200);
  WiFi.softAPConfig(local_IP, gateway, subnet);

  dnsServer.start(53, "*", local_IP);

//  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
//    request->send(SPIFFS, "/index.html");
//  });
//
//  server.on("/m", HTTP_GET, [] (AsyncWebServerRequest * request) {
//    if (request->hasParam("message")) {
//      message = request->getParam("message")->value();
//      LoRaSend(message);
//      request->send(200, "text/html", "Your message has been sent!:\n"
//                    + message + "<br><a href=\"/\">Return to Home Page</a>");
//    } else {
//      request->send(404, "text/plain", "Not found");
//    }
//  });

  urlDefine();

  server.begin();
  Serial.print("Server started at 192.168.1.0");
}

void loop() {
}

void LoRaSend(String messageSend) {
  LoRa.beginPacket();
  Lora.print()
  LoRa.print("Message: "); LoRa.print(messageSend);
  LoRa.endPacket();
  Serial.print("Message sent: "); Serial.println(message);
}

void urlDefine(){
  server.onNotFound([]() {
    request->send(SPIFFS, "/index.html");
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });
  
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });

  server.on("/contacts.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/contacts.html");
  });

  server.on("/messages.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/messages.html");
  });

  server.on("/newContact.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/newContact.html");
  });

  server.on("/m", HTTP_GET, [] (AsyncWebServerRequest * request) {
    if (request->hasParam("message")) {
      message = request->getParam("message")->value();
      LoRaSend(message);
      request->send(200, "text/html", "Your message has been sent!:\n"
                    + message + "<br><a href=\"/\">Return to Home Page</a>");
    } else {
      request->send(404, "text/plain", "Not found");
    }
  });

  server.on("/u", HTTP_GET, [] (AsyncWebServerRequest * request) {
      if (request->hasParam("name") && request->hasParam("number") && request->hasParam("secret")) {
        String userName = request->getParam("name")->value();
        String userSecret = request->getParam("secret")->value();
        String tempNumber = request->getParam("name")->value();
        int userNumber = number.toInt();
        
        request->send(200, "text/html", "User has been added:\n" + userName + "<br><a href=\"/\">Return to Home Page</a>");
      } else {
        request->send(404, "text/plain", "Missing fields");
      }
    });
  
  }
