# Scale Setup

`ScaleHX711` in the firmware is a lightweight shim that uses the ADC to avoid external dependencies. When you are ready to integrate a real HX711 breakout, replace the implementation with the library of your choice while preserving the public API.

## Workflow
1. Wire DT to GPIO 32 and SCK to GPIO 33.
2. Update `pressureScale` in `GlobalConfig.h` to convert raw units to bar.
3. Trigger `tare()` after warm-up to remove drift.
