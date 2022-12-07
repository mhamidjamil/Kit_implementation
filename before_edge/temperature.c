
#include <MySignals.h>

#include "SPI.h"
#include "Wire.h"

void setup() {
  Serial.begin(115200);

  MySignals.begin();
}

void loop() {
  float temperature = MySignals.getTemperature();
  Serial.print("Temperature (*C): <1_");
  Serial.print(temperature, 2);
  Serial.println("_1>");

  // Serial.println(temperature, 2);

  delay(1000); // wait for a second
}
