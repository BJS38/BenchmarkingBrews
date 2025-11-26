#include "BLEBattery.h"

BLEBattery::BLEBattery(const char *serviceUuid, const char *characteristicUuid)
    : _service(serviceUuid), _levelCharacteristic(characteristicUuid, BLERead | BLENotify) {}

bool BLEBattery::begin() {
    BLE.setAdvertisedService(_service);
    _service.addCharacteristic(_levelCharacteristic);
    return BLE.addService(_service);
}

void BLEBattery::updateLevel(float voltage, float fullVoltage, float emptyVoltage) {
    voltage = constrain(voltage, emptyVoltage, fullVoltage);
    float level = 100.0f * ((voltage - emptyVoltage) / (fullVoltage - emptyVoltage));
    uint8_t value = static_cast<uint8_t>(level);
    if (millis() - _lastUpdate > 1000 || !_levelCharacteristic.written() || _levelCharacteristic.value() != value) {
        _levelCharacteristic.writeValue(value);
        _lastUpdate = millis();
    }
}

void BLEBattery::poll() {
    // Placeholder for future battery-specific events.
}
