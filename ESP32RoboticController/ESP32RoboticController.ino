#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <lwip/sockets.h>
#include <esp_heap_caps.h>
#include "src/RoboticConstructor/BittleQuadrupedConstructor.h"
#include "src/RoboticController.h"


namespace {
  constexpr int kSerialBaud   = 115200;
  constexpr int kLoopPeriodMs = 20;  // 50 Hz

  void printMemoryUsage() {
    Serial.print(F("Free heap: "));
    Serial.println(esp_get_free_heap_size());
  }
}

BittleQuadrupedConstructor* pConstructor = nullptr;
RoboticController*          pController  = nullptr;

void setup() {
  Serial.begin(kSerialBaud);
  delay(2000);
  Serial.println(F("[ESP32 Robot] Booting up..."));
  delay(1000);

  // now it’s safe to construct things that touch WiFi, heap, timers, etc.
  pConstructor = new BittleQuadrupedConstructor();
  pController  = new RoboticController(*pConstructor);
}

void loop() {
  // printMemoryUsage();  // enable when you need it
 // pController->RunControllerLoop();
 pController->RunServos();
  vTaskDelay(pdMS_TO_TICKS(kLoopPeriodMs));
}
