#pragma once

#include <Arduino.h>

class ScaleHX711 {
  public:
    ScaleHX711(uint8_t dataPin, uint8_t clockPin) : _dataPin(dataPin), _clockPin(clockPin) {}

    void begin() {
        pinMode(_dataPin, INPUT);
        pinMode(_clockPin, OUTPUT);
        tare();
    }

    void tare() { _offset = analogRead(_dataPin); }

    float getGrams() {
        int raw = analogRead(_dataPin);
        int diff = raw - _offset;
        return diff * _scale;
    }

    void setScale(float scale) { _scale = scale; }

  private:
    uint8_t _dataPin;
    uint8_t _clockPin;
    int _offset = 0;
    float _scale = 1.0f;
};
