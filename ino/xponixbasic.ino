#include <OneWire.h>
#include <DallasTemperature.h>

int sensorPin = 2;
OneWire oneWire(sensorPin);
DallasTemperature sensors(&oneWire);

int pumpPin = 12;
// unsigned long intervalTime = 14400000; // 4 h
unsigned long intervalTime = 1440; // 1.44 sec
// unsigned long pumpingTime = 1200000; // 20 min
unsigned long pumpingTime = 120; // 0.12 sec
unsigned long breakTime = intervalTime - pumpingTime;

float temp; // celsius

void setup()
{
    Serial.begin(9600);
    sensors.begin();
}

void loop()
{
    sensors.requestTemperatures();
    temp = sensors.getTempCByIndex(0);
    Serial.println(temp);

    if (temp > 25) {
        intervalTime = 360;
    } else if (temp > 20) {
        intervalTime = 720;
    } else {
        intervalTime = 1440;
    }

    breakTime = intervalTime - pumpingTime;

    digitalWrite(pumpPin, HIGH);
    delay(pumpingTime);
    digitalWrite(pumpPin, LOW);
    delay(breakTime);
}
