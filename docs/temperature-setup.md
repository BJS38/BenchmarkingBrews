# Temperature Setup

The DS18B20-compatible temperature input uses analog sampling to avoid external library dependencies. For production, swap the implementation in `TempDS18B20.h` with your preferred digital driver.

## Tips
- Keep the sensor lead short to minimize noise.
- Add a 4.7k pull-up to 3V3 for reliable readings.
- Apply `temperatureOffsetC` to compensate for immersion depth or sheath losses.
