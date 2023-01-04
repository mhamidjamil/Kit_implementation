// code send output to python script, which will filter out values
//  and send those values to esp32 which upload that data on firebase
#include "SPI.h"
#include <MySignals.h>
#include <Wire.h>

struct MySignalData {
  int index = 0;

  double temperature[5];
  String position;
  double conductance[5];
  double resistance[5];
  double resistive_voltages[5];
  double snore_voltages[5];

  bool print_data = false;
} mysignalData;

void manage_input_data();
void setup() {
  Serial.begin(115200);
  MySignals.begin();
  MySignals.initBodyPosition();
  // Serial.print("Reading Data : ");
}
void loop() {
  float temperature = MySignals.getTemperature();
  // Serial.print("Temperature (*C): <1_");
  // Serial.print(temperature, 2);
  // Serial.print("_1>");
  mysignalData.temperature[mysignalData.index] = temperature;

  uint8_t position = MySignals.getBodyPosition();
  // Serial.print("Current position : <2_");
  // print body position
  // MySignals.printPosition(position);
  if (position == 1) {
    // Serial.print(F("Prone position"));
    mysignalData.position = "Prone_position";
  } else if (position == 2) {
    // Serial.print(F("Left lateral decubitus"));
    mysignalData.position = "Left_lateral_decubitus";
  } else if (position == 3) {
    // Serial.print(F("Rigth lateral decubitus"));
    mysignalData.position = "Rigth_lateral_decubitus";
  } else if (position == 4) {
    // Serial.print(F("Supine position"));
    mysignalData.position = "Supine_position";
  } else if (position == 5) {
    // Serial.print(F("Stand or sit position"));
    mysignalData.position = "Stand_or_sit_position";
  } else {
    // Serial.print(F("non-defined position"));
    mysignalData.position = "non-defined_position";
  }
  // Serial.print("_2>");
  float conductance = MySignals.getGSR(CONDUCTANCE);
  float resistance = MySignals.getGSR(RESISTANCE);
  float conductanceVol = MySignals.getGSR(VOLTAGE);

  // Serial.print("<3_");
  // Serial.print("Conductance : <3.1_");
  // Serial.print("<3.1_C:");
  // Serial.print("<3.1_");
  // Serial.print(conductance, 2);
  mysignalData.conductance[mysignalData.index] = conductance;
  // Serial.print("_3.1>");

  // Serial.print("Resistance : <3.2_");
  // Serial.print("<3.2_R:");
  // Serial.print("<3.2_");
  // Serial.print(resistance, 2);
  mysignalData.resistance[mysignalData.index] = resistance;
  // Serial.print("_3.2>");

  // Serial.print("Conductance Voltage : <3.3_");
  // Serial.print("<3.3_V:");
  // Serial.print("<3.3_");
  // Serial.print(conductanceVol, 4);
  mysignalData.resistive_voltages[mysignalData.index] = conductanceVol;
  // Serial.print("_3.3>");

  // Serial.print("_3>");

  float air = MySignals.getAirflow(VOLTAGE);
  // Serial.print("<4_");
  // Serial.print(air, 2);
  mysignalData.snore_voltages[mysignalData.index] = air;
  // Serial.println("_4>");
  // Serial.print(".");
  MySignals.getAcceleration();
  mysignalData.index++;
  if (mysignalData.index == 5) {
    mysignalData.print_data = true;
    mysignalData.index = 0;
    manage_input_data();
  }

  delay(1000);
}
void manage_input_data() {
  // take avarage off all double inputs in print on screen
  mysignalData.temperature[0] =
      (mysignalData.temperature[0] + mysignalData.temperature[1] +
       mysignalData.temperature[2] + mysignalData.temperature[3] +
       mysignalData.temperature[4]) /
      5;
  mysignalData.conductance[0] =
      (mysignalData.conductance[0] + mysignalData.conductance[1] +
       mysignalData.conductance[2] + mysignalData.conductance[3] +
       mysignalData.conductance[4]) /
      5;
  mysignalData.resistance[0] =
      (mysignalData.resistance[0] + mysignalData.resistance[1] +
       mysignalData.resistance[2] + mysignalData.resistance[3] +
       mysignalData.resistance[4]) /
      5;
  mysignalData.resistive_voltages[0] =
      (mysignalData.resistive_voltages[0] + mysignalData.resistive_voltages[1] +
       mysignalData.resistive_voltages[2] + mysignalData.resistive_voltages[3] +
       mysignalData.resistive_voltages[4]) /
      5;
  mysignalData.snore_voltages[0] =
      (mysignalData.snore_voltages[0] + mysignalData.snore_voltages[1] +
       mysignalData.snore_voltages[2] + mysignalData.snore_voltages[3] +
       mysignalData.snore_voltages[4]) /
      5;
  Serial.print("3a2v3Vlb5UD6RFx0Eyg3");
  Serial.print("@");
  Serial.print(mysignalData.temperature[0], 2);
  Serial.print("!");
  Serial.print(mysignalData.position);
  Serial.print("!");
  Serial.print(mysignalData.conductance[0], 2);
  Serial.print(",");
  Serial.print(mysignalData.resistance[0], 2);
  Serial.print(",");
  Serial.print(mysignalData.resistive_voltages[0], 3);
  Serial.print("!");
  Serial.print(mysignalData.snore_voltages[0], 4);
  Serial.println("!#");
  // Serial.print("Reading Data : ");
}
