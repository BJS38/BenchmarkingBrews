#pragma once

#include <ArduinoBLE.h>
#include <Arduino.h>

class OEPLog {
  public:
    explicit OEPLog(const char *characteristicUuid);
    void begin(BLEService &service);
    void publish(const String &message);

  private:
    BLEStringCharacteristic _logCharacteristic;
};
