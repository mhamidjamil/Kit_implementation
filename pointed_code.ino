
#include "SPI.h"
#include <MySignals.h>
#include <Wire.h>

void setup()
{
    Serial.begin(115200);
    MySignals.begin();
    MySignals.initBodyPosition();
}

void loop()
{
    float temperature = MySignals.getTemperature();
    Serial.print("Current position : <2_");
    Serial.print(temperature, 2);
    Serial.print("_1>");
    uint8_t position = MySignals.getBodyPosition();
    Serial.print("Current position : <");
    // print body position
    // MySignals.printPosition(position);
    if (position == 1)
    {
        Serial.print(F("Prone position"));
    }
    else if (position == 2)
    {
        Serial.print(F("Left lateral decubitus"));
    }
    else if (position == 3)
    {
        Serial.print(F("Rigth lateral decubitus"));
    }
    else if (position == 4)
    {
        Serial.print(F("Supine position"));
    }
    else if (position == 5)
    {
        Serial.print(F("Stand or sit position"));
    }
    else
    {
        Serial.print(F("non-defined position"));
    }
    Serial.println("_2>");
    delay(100);

    // print acc values
    MySignals.getAcceleration();

    // convert float to strintg
    // char bufferAcc[50];
    // char x_acc_string[10];
    // char y_acc_string[10];
    // char z_acc_string[10];
    // dtostrf(MySignals.x_data, 2, 2, x_acc_string);
    // dtostrf(MySignals.y_data, 2, 2, y_acc_string);
    // dtostrf(MySignals.z_data, 2, 2, z_acc_string);

    // // print the X Y Z acceleration
    // sprintf(bufferAcc, "Acceleration: X= %s  Y= %s  Z= %s  ", x_acc_string,
    //         y_acc_string, z_acc_string);
    // Serial.println(bufferAcc);

    delay(1000);
}
