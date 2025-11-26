#include "OEPPressure.h"

OEPPressure::OEPPressure(const char *pressureUuid, const char *temperatureUuid)
    : _pressureCharacteristic(pressureUuid, BLENotify | BLERead),
      _temperatureCharacteristic(temperatureUuid, BLENotify | BLERead) {}

void OEPPressure::begin(BLEService &service) {
    service.addCharacteristic(_pressureCharacteristic);
    service.addCharacteristic(_temperatureCharacteristic);
    _pressureCharacteristic.writeValue(0.0f);
    _temperatureCharacteristic.writeValue(0.0f);
}

void OEPPressure::update(float pressureBar, float temperatureC) {
    _pressureCharacteristic.writeValue(pressureBar);
    _temperatureCharacteristic.writeValue(temperatureC);
}
