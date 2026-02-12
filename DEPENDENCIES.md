# ESP32 Bluetooth Game Controller - Library Dependencies

## Arduino Libraries Required

### 1. ESP32-BLE-Gamepad
- **Version**: 0.5.0 or higher
- **Author**: lemmingDev
- **Description**: Bluetooth Low Energy Gamepad library for ESP32
- **Installation**: 
  - Arduino IDE: Library Manager → Search "ESP32-BLE-Gamepad"
  - Or download from: https://github.com/lemmingDev/ESP32-BLE-Gamepad

### 2. ESP32 Board Support
- **Package**: esp32 by Espressif Systems
- **Version**: 2.0.0 or higher
- **Installation**:
  - Add to Arduino IDE Board Manager URLs:
    ```
    https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
    ```
  - Install via Tools → Board → Boards Manager

## PlatformIO Configuration (Alternative)

If using PlatformIO instead of Arduino IDE, add to `platformio.ini`:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps = 
    lemmingDev/ESP32-BLE-Gamepad@^0.5.0
monitor_speed = 115200
```

## System Requirements

### PC Requirements for Bluetooth Connection
- **Operating System**: Windows 10/11, Linux (kernel 5.0+), or macOS 10.15+
- **Bluetooth**: Bluetooth 4.0 (BLE) or higher
- **Drivers**: Standard HID gamepad drivers (built-in)

### Development Requirements
- **Arduino IDE**: Version 1.8.13 or higher (or Arduino IDE 2.x)
- **Python**: 2.7 or 3.5+ (required for ESP32 tools)
- **USB Driver**: CP210x or CH340 USB-to-Serial driver (depending on ESP32 board)

## Optional Libraries

### For Advanced Features

1. **Preferences** (Built-in ESP32)
   - For storing calibration data in non-volatile memory
   - No installation needed

2. **Wire** (Built-in Arduino)
   - For I2C communication with additional sensors
   - No installation needed

3. **SPIFFS** (Built-in ESP32)
   - For file system operations
   - No installation needed

## USB Driver Installation

### Windows
1. Download CP210x driver from Silicon Labs website
2. Or CH340 driver from WCH website
3. Install and restart computer

### macOS
- Usually works out of the box
- If needed, install CP210x driver from Silicon Labs

### Linux
- Drivers usually included in kernel
- Add user to dialout group:
  ```bash
  sudo usermod -a -G dialout $USER
  ```
- Logout and login for changes to take effect

## Verification

After installing dependencies, verify in Arduino IDE:
1. File → Examples → ESP32-BLE-Gamepad → should show example sketches
2. Tools → Board → should show ESP32 boards
3. Sketch → Verify/Compile → should compile without errors

## Troubleshooting Library Issues

### ESP32-BLE-Gamepad not found
- Restart Arduino IDE after installation
- Check Library Manager for successful installation
- Manually download and place in Arduino libraries folder

### Compilation Errors
- Update ESP32 board package to latest version
- Update ESP32-BLE-Gamepad library to latest version
- Check Arduino IDE version (use 1.8.13+)

### Bluetooth Pairing Issues
- Update PC Bluetooth drivers
- Check Windows/Linux/macOS Bluetooth compatibility
- Try removing and re-pairing device

## Version Compatibility

| Component | Minimum Version | Recommended Version |
|-----------|----------------|---------------------|
| Arduino IDE | 1.8.13 | 2.2.1 or higher |
| ESP32 Core | 2.0.0 | 2.0.14 or higher |
| ESP32-BLE-Gamepad | 0.5.0 | Latest |
| Python | 2.7 / 3.5 | 3.9 or higher |

## Additional Resources

- ESP32-BLE-Gamepad Documentation: https://github.com/lemmingDev/ESP32-BLE-Gamepad
- ESP32 Arduino Core: https://github.com/espressif/arduino-esp32
- Arduino IDE Download: https://www.arduino.cc/en/software
- PlatformIO: https://platformio.org/
