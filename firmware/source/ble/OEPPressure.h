#pragma once

#include <ArduinoBLE.h>
#include <Arduino.h>

class OEPPressure {
  public:
    OEPPressure(const char *pressureUuid, const char *temperatureUuid);
    void begin(BLEService &service);
    void update(float pressureBar, float temperatureC);

  private:
    BLEFloatCharacteristic _pressureCharacteristic;
    BLEFloatCharacteristic _temperatureCharacteristic;
};
