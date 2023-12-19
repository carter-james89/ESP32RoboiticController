#include <ArduinoJson.h>

#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <lwip/sockets.h>

#include "RoboticController.h"
#include "QuadrupedConfiguration.h"
#include "RoboticController.h"
#include "BittleQuadrupedConstructor.h"

#include <esp_heap_caps.h>

void printMemoryUsage() {
    Serial.print("Free heap: ");
    Serial.println(esp_get_free_heap_size());

    // Serial.print("Minimum ever free heap size: ");
    // Serial.println(esp_get_minimum_free_heap_size());

    // size_t total_heap = heap_caps_get_total_size(MALLOC_CAP_8BIT);
    // size_t free_heap = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    // size_t largest_block = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);

    // // Serial.print("Total heap: ");
    // Serial.println(total_heap);
  //  Serial.print("Free heap: ");
  //  Serial.println(free_heap);
    // Serial.print("Largest free block: ");
    // Serial.println(largest_block);
    // Serial.print("Heap fragmentation: ");
    // Serial.print(100 - (largest_block * 100 / free_heap));
    // Serial.println("%");
}

//RoboticController _roboticController;
unsigned long lastPrintTime = 0; // Last time the loops per second were printed
unsigned long loopCount = 0;     // Number of loops since last print

//BittleQuadrupedConfiguration config; 
RoboticController* _roboticController;
BittleQuadrupedConstructor constructor;

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
    delay(2000);
  Serial.println("Robot bootup");

  delay(5000);

 //  _roboticController = RoboticController(config); 
 _roboticController = new RoboticController(constructor);

 delay(5000);
 //config.OnConstructionComplete();

}
void loop() {
  printMemoryUsage();
  _roboticController->RunControllerLoop();
   delay(100);



 return;
   // delay(100);

    loopCount++; // Increment the loop counter

    // Check if a second has passed (1000 milliseconds)
    if (millis() - lastPrintTime >= 1000) {
        // Reset the counter and the last print time
        loopCount = 0;
        lastPrintTime = millis();
    }
}