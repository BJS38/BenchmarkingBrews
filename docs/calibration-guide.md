# Calibration Guide

The firmware exposes smoothing and scaling factors through `GlobalConfig.h`. Tweak these values and rebuild via PlatformIO for best accuracy.

## Scale calibration
1. Open `firmware/source/GlobalConfig.h` and set `pressureScale` to your HX711 grams-to-bar conversion.
2. Flash the firmware and place a known calibration weight on the portafilter.
3. Read the pressure in the web tool and adjust until it matches the expected reference.

## Temperature calibration
1. Place the probe in a known temperature bath.
2. Adjust `temperatureOffsetC` in `GlobalConfig.h` until readings align.

## Battery calibration
Set `batteryFullVoltage` and `batteryEmptyVoltage` to match your cell chemistry (4.20 V / 3.30 V by default).
