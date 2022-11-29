
#include "SPI.h"
#include "Wire.h"
#include <MySignals.h>

void setup() {
  Serial.begin(115200);

  MySignals.begin();
}

void loop() {

  float conductance = MySignals.getGSR(CONDUCTANCE);
  float resistance = MySignals.getGSR(RESISTANCE);
  float conductanceVol = MySignals.getGSR(VOLTAGE);

  Serial.print("<3_");
  Serial.print("Conductance : <3.1_");
  Serial.print("C:");
  Serial.print(conductance, 2);
  Serial.print("_3.1>");

  Serial.print("Resistance : <3.2_");
  Serial.print("R:");
  Serial.print(resistance, 2);
  Serial.print("_3.2>");

  Serial.print("Conductance Voltage : <3.3_");
  Serial.print("V:");
  Serial.print(conductanceVol, 4);
  Serial.print("_3.3>");

  Serial.println("_3>");
  // Serial.print("Conductance : ");
  // Serial.print(conductance, 2);
  // Serial.println("");

  // Serial.print("Resistance : ");
  // Serial.print(resistance, 2);
  // Serial.println("");

  // Serial.print("Conductance Voltage : ");
  // Serial.print(conductanceVol, 4);
  // Serial.println("");

  // Serial.print("\n");

  // wait for a second
  delay(1000);
}
