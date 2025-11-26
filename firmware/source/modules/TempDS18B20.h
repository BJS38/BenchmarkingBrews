#pragma once

#include <Arduino.h>

class TempDS18B20 {
  public:
    explicit TempDS18B20(uint8_t pin) : _pin(pin) {}

    void begin() {
        pinMode(_pin, INPUT);
    }

    float readCelsius() {
        // Placeholder analog read scaled to a plausible temperature range.
        int raw = analogRead(_pin);
        float voltage = (raw / 4095.0f) * 3.3f;
        return (voltage * 100.0f) + _offsetC;
    }

    void setOffset(float offsetC) { _offsetC = offsetC; }

  private:
    uint8_t _pin;
    float _offsetC = 0.0f;
};
