#pragma once

#include <Arduino.h>

struct GlobalConfig {
    const char *deviceName = "BenchmarkingBrews";
    float pressureScale = 1.0f;
    float temperatureOffsetC = 0.0f;
    float batteryFullVoltage = 4.2f;
    float batteryEmptyVoltage = 3.3f;
    float movingAverageAlpha = 0.25f;
};

inline GlobalConfig &config() {
    static GlobalConfig cfg;
    return cfg;
}
