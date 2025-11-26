#include "OEPLog.h"

OEPLog::OEPLog(const char *characteristicUuid)
    : _logCharacteristic(characteristicUuid, BLERead | BLENotify, 64) {}

void OEPLog::begin(BLEService &service) {
    service.addCharacteristic(_logCharacteristic);
    _logCharacteristic.writeValue(String("Booting"));
}

void OEPLog::publish(const String &message) {
    _logCharacteristic.writeValue(message);
}
