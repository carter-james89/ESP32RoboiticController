/**
 * @file main.ino
 * @brief Entry point for the ESP32 quadruped RoboticController example.
 *
 * Sets up serial, constructs the quadruped and controller,
 * then runs the control loop at a fixed interval.
 */

 #include <Arduino.h>
 #include <ArduinoJson.h>
 #include <WiFiClient.h>
 #include <WiFiServer.h>
 #include <WiFiUdp.h>
 #include <lwip/sockets.h>
 #include <esp_heap_caps.h>
 
 #include "BittleQuadrupedConstructor.h"
 #include "RoboticController.h"
 
 /**
  * @brief Print current heap usage to Serial.
  */
 static void printMemoryUsage() {
     Serial.print(F("Free heap: "));
     Serial.println(esp_get_free_heap_size());
     // Uncomment below for more detailed stats:
     // size_t total = heap_caps_get_total_size(MALLOC_CAP_8BIT);
     // size_t free = heap_caps_get_free_size(MALLOC_CAP_8BIT);
     // size_t largest = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
     // Serial.print(F("Total heap: ")); Serial.println(total);
     // Serial.print(F("Largest block: ")); Serial.println(largest);
 }
 
 /**
  * @brief Constructs the quadruped using predefined limb topology.
  */
 static BittleQuadrupedConstructor constructor;
 
 /**
  * @brief Main controller instance managing network, sensors, and servos.
  */
 static RoboticController roboticController(constructor);
 
 /**
  * @brief Arduino setup: initializes Serial and prints startup banner.
  */
 void setup() {
     Serial.begin(115200);
     delay(2000);
     Serial.println(F("[ESP32 Robot] Booting up..."));
     delay(1000);
 }
 
 /**
  * @brief Main loop: invokes the controller at ~50Hz.
  */
 void loop() {
     // printMemoryUsage();  // enable to debug memory usage
     roboticController.RunControllerLoop();
     delay(20);  // loop period (ms)
 }
 