#include <Arduino.h>
#include <ArduinoBLE.h>

#include "GlobalConfig.h"
#include "ble/BLEBattery.h"
#include "ble/OEPLog.h"
#include "ble/OEPPressure.h"
#include "config.h"
#include "modules/ScaleHX711.h"
#include "modules/TempDS18B20.h"

ScaleHX711 scale(PIN_SCALE_DATA, PIN_SCALE_CLOCK);
TempDS18B20 tempSensor(PIN_TEMP_SENSOR);
BLEBattery battery(OEP_BATTERY_SERVICE_UUID, OEP_BATTERY_CHARACTERISTIC_UUID);
BLEService oepService(OEP_SERVICE_UUID);
OEPPressure pressure(OEP_PRESSURE_CHARACTERISTIC_UUID, OEP_TEMPERATURE_CHARACTERISTIC_UUID);
OEPLog logger(OEP_LOG_CHARACTERISTIC_UUID);

unsigned long lastSensorRead = 0;

float movingAverage(float previous, float current) {
    return (config().movingAverageAlpha * current) + ((1.0f - config().movingAverageAlpha) * previous);
}

float readBatteryVoltage() {
    int raw = analogRead(PIN_BATTERY);
    float voltage = (raw / 4095.0f) * 2.0f * 1.1f; // account for voltage divider and internal ref
    return voltage;
}

void setupSensors() {
    scale.begin();
    scale.setScale(config().pressureScale);
    tempSensor.begin();
    tempSensor.setOffset(config().temperatureOffsetC);
}

bool setupBLE() {
    if (!BLE.begin()) {
        Serial.println("Failed to initialize BLE");
        return false;
    }

    BLE.setDeviceName(config().deviceName);
    BLE.setLocalName(config().deviceName);

    if (!battery.begin()) {
        Serial.println("Failed to start battery service");
        return false;
    }

    pressure.begin(oepService);
    logger.begin(oepService);

    if (!BLE.addService(oepService)) {
        Serial.println("Failed to add OEP service");
        return false;
    }

    BLE.advertise();
    Serial.print("Advertising as ");
    Serial.println(config().deviceName);
    return true;
}

void setup() {
    Serial.begin(115200);
    while (!Serial)
        ;

    setupSensors();
    if (!setupBLE()) {
        // Nothing else to do if BLE fails, but keep the loop alive.
        return;
    }
    logger.publish("Firmware ready");
}

void loop() {
    BLE.poll();
    battery.poll();

    if (millis() - lastSensorRead >= SENSOR_READ_INTERVAL_MS) {
        lastSensorRead = millis();
        static float smoothedPressure = 0.0f;
        static float smoothedTemp = 0.0f;

        float grams = scale.getGrams();
        float pressureBar = grams * 0.01f; // placeholder conversion
        float tempC = tempSensor.readCelsius();

        smoothedPressure = movingAverage(smoothedPressure, pressureBar);
        smoothedTemp = movingAverage(smoothedTemp, tempC);

        pressure.update(smoothedPressure, smoothedTemp);

        float batteryVoltage = readBatteryVoltage();
        battery.updateLevel(batteryVoltage, config().batteryFullVoltage, config().batteryEmptyVoltage);

        logger.publish(String("P:") + smoothedPressure + "bar T:" + smoothedTemp + "C V:" + batteryVoltage + "V");
    }
}
