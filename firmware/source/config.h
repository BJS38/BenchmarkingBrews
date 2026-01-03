#pragma once

#include <Arduino.h>

// Pin configuration for the BenchmarkingBrews probe hardware.
static const uint8_t PIN_SCALE_DATA = 32;
static const uint8_t PIN_SCALE_CLOCK = 33;
static const uint8_t PIN_TEMP_SENSOR = 34;
static const uint8_t PIN_BATTERY = 35;

// BLE identifiers for the Open Espresso Protocol (OEP) services.
static const char *const OEP_SERVICE_UUID = "e7b01b7f-39b7-4602-8d02-f5b88c7a9b5a";
static const char *const OEP_PRESSURE_CHARACTERISTIC_UUID = "5c68f082-5a7c-4028-a24c-6c6c0ce3c4b2";
static const char *const OEP_TEMPERATURE_CHARACTERISTIC_UUID = "3f3b4e6d-7a2a-4c57-94d9-22461c9c4b71";
static const char *const OEP_LOG_CHARACTERISTIC_UUID = "d9e7b13a-6c0c-4c22-8e4a-1e6162b23c53";
static const char *const OEP_BATTERY_SERVICE_UUID = "180F";
static const char *const OEP_BATTERY_CHARACTERISTIC_UUID = "2A19";

// Timing parameters.
static const unsigned long SENSOR_READ_INTERVAL_MS = 500;
static const unsigned long BLE_ADVERTISING_INTERVAL_MS = 1000;
