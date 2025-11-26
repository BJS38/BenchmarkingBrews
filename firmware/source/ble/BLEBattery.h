#pragma once

#include <ArduinoBLE.h>
#include <Arduino.h>

class BLEBattery {
  public:
    BLEBattery(const char *serviceUuid, const char *characteristicUuid);
    bool begin();
    void updateLevel(float voltage, float fullVoltage, float emptyVoltage);
    void poll();

  private:
    BLEService _service;
    BLEUnsignedCharCharacteristic _levelCharacteristic;
    unsigned long _lastUpdate = 0;
};
