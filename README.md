# BenchmarkingBrews

ESP32-based espresso pressure and temperature probe with BLE, OLED-friendly firmware, and a Web Bluetooth calibration console.

## Layout
- `firmware/` — PlatformIO project for the BLE probe
  - `source/main.cpp` — firmware entry point wiring up sensors and BLE services
  - `source/ble/` — Open Espresso Protocol characteristics and battery service
  - `source/modules/` — lightweight sensor shims for the scale and temperature inputs
- `web-tool/` — static Web Bluetooth console for viewing pressure, temperature, battery, and logs
- `docs/` — setup, calibration, and troubleshooting guides
- `.github/workflows/` — CI build that compiles the firmware with PlatformIO

## Getting started
1. Install [PlatformIO](https://platformio.org/).
2. From `firmware/`, run `pio run` to build or `pio run -t upload` to flash.
3. Open `web-tool/index.html` in a Web Bluetooth–capable browser and click **Connect via BLE** to view live data.

## License
MIT. See `LICENSE` for details.
