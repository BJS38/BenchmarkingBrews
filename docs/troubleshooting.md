# Troubleshooting

| Symptom | Potential Cause | Fix |
| --- | --- | --- |
| BLE device not found | Browser lacks Web Bluetooth, or device not advertising | Use Chrome/Edge, ensure ESP32 is powered and advertising (serial log should say `Advertising as ...`). |
| Pressure reads zero | HX711 pins not wired or wrong scale factor | Verify DT/SCK wiring and adjust `pressureScale` in `GlobalConfig.h`. |
| Temperature unstable | Long sensor leads or missing pull-up | Keep leads short and add a 4.7k pull-up resistor to 3V3. |
| Battery always 100% | Voltage divider not matched to ADC range | Recalculate resistor values so full battery maps near 1.1 V. |
