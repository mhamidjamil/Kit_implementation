// arduino listen at pin 2 and 3 (data coming from MySignal kit) and print on screen

#include <SoftwareSerial.h>

SoftwareSerial Mysignal(2, 3);
void setup()
{
    Serial.begin(115200);
    Mysignal.begin(115200);
}

void loop()
{
    String tempStr = "";
    if (Mysignal.available() > 0)
    {
        while (Mysignal.available())
        {
            tempStr = Mysignal.readStringUntil('#');
        }
        Serial.println(tempStr);
    }
}