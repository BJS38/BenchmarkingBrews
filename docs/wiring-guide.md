# Wiring Guide

This guide documents the pinout for the BenchmarkingBrews probe when using an ESP32-DevKitC style board.

## Pin assignments
- **Scale HX711**
  - DT -> GPIO 32 (`PIN_SCALE_DATA`)
  - SCK -> GPIO 33 (`PIN_SCALE_CLOCK`)
  - VCC -> 3V3, GND -> GND
- **Temperature sensor** (DS18B20 on analog input)
  - Signal -> GPIO 34 (`PIN_TEMP_SENSOR`)
  - VCC -> 3V3, GND -> GND
  - 4.7k pull-up between signal and 3V3
- **Battery monitor**
  - Voltage divider output -> GPIO 35 (`PIN_BATTERY`)
  - Choose resistors that scale battery max voltage to ~1.1 V ADC range.

## BLE indicator
The firmware advertises as `BenchmarkingBrews` by default. You can edit the name inside `GlobalConfig.h` if desired.
