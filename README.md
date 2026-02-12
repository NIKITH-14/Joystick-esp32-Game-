# ESP32 Bluetooth Game Controller 🎮

A wireless Bluetooth HID gamepad using ESP32 and dual analog joysticks, designed for PC racing games like Asphalt. Features steering control, speed control (throttle/brake), and pause functionality.

## 🌟 Features

- **Wireless Bluetooth Connection**: Connects to PC as a standard HID gamepad
- **Dual Analog Joysticks**: 
  - Left joystick: Steering (X-axis) and Speed control (Y-axis)
  - Right joystick: Additional control inputs
- **Button Controls**: Multiple buttons including pause/menu functionality
- **Smooth Input**: Exponential moving average filter for responsive yet smooth control
- **Deadzone Support**: Configurable deadzone to prevent drift
- **PC Compatible**: Works with Windows, Linux, and macOS
- **Low Latency**: ~100Hz update rate for responsive gaming

## 🎯 Perfect For

- Racing games (Asphalt, Need for Speed, Forza Horizon, etc.)
- Flight simulators
- Custom game projects
- Robotics control
- Any application requiring dual analog input

## 📦 Hardware Requirements

### Components
- **ESP32 Development Board** (ESP32-WROOM-32 or similar)
- **2x Analog Joystick Modules** (KY-023 or compatible)
- **1x Push Button** (optional, for dedicated pause)
- **Breadboard and Jumper Wires**
- **USB Cable** (for programming and power)
- **Optional**: Battery pack for portable operation

### Cost
Total project cost: ~$10-15 USD

## 🔧 Setup Instructions

### 1. Install Arduino IDE and ESP32 Support

1. Download and install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board support:
   - Go to `File` → `Preferences`
   - Add to "Additional Board Manager URLs":
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Go to `Tools` → `Board` → `Boards Manager`
   - Search for "esp32" and install "esp32 by Espressif Systems"

### 2. Install Required Libraries

Install the BleGamepad library:
1. Go to `Sketch` → `Include Library` → `Manage Libraries`
2. Search for "ESP32-BLE-Gamepad"
3. Install "ESP32-BLE-Gamepad" by lemmingDev

### 3. Hardware Assembly

Follow the detailed wiring guide in [WIRING.md](WIRING.md) to connect:
- Left joystick to GPIO 34, 35, 32
- Right joystick to GPIO 36, 39, 33
- Optional pause button to GPIO 25

**Quick Pin Reference:**
```
Left Joystick:  VRx→GPIO34, VRy→GPIO35, SW→GPIO32
Right Joystick: VRx→GPIO36, VRy→GPIO39, SW→GPIO33
Pause Button:   GPIO25 to GND
Power: 3.3V and GND to both joysticks
```

### 4. Upload the Code

1. Open `ESP32_BT_Gamepad.ino` in Arduino IDE
2. Select your ESP32 board:
   - `Tools` → `Board` → `ESP32 Arduino` → `ESP32 Dev Module`
3. Select the correct COM port:
   - `Tools` → `Port` → Select your ESP32's port
4. Click the Upload button (→)
5. Wait for "Done uploading" message

### 5. Connect to PC

1. **Windows**:
   - Go to `Settings` → `Bluetooth & devices`
   - Click "Add device" → "Bluetooth"
   - Select "ESP32 Racing Controller"
   - Once connected, go to `Control Panel` → `Devices and Printers`
   - Right-click on the gamepad and select "Game controller settings"
   - Click "Properties" to test inputs

2. **Linux**:
   ```bash
   bluetoothctl
   scan on
   pair [ESP32 MAC Address]
   connect [ESP32 MAC Address]
   trust [ESP32 MAC Address]
   ```

3. **macOS**:
   - Go to `System Preferences` → `Bluetooth`
   - Click "Connect" next to "ESP32 Racing Controller"

## 🎮 Usage

### Controller Mapping

| Input | Function | Gaming Use |
|-------|----------|------------|
| Left Joystick X-axis | Steering | Turn left/right |
| Left Joystick Y-axis | Speed | Throttle/Brake |
| Left Joystick Button | Action Button 1 | Nitro/Boost |
| Right Joystick X-axis | Camera/View | Look left/right |
| Right Joystick Y-axis | Camera/View | Look up/down |
| Right Joystick Button | Pause/Menu | Pause game |
| Pause Button | Pause/Menu | Pause game |

### In Racing Games

1. **Start the game** and go to controller settings
2. **Map controls**:
   - Steering: Left stick horizontal
   - Throttle: Left stick forward
   - Brake: Left stick backward
   - Pause: Start button (right joystick press)
3. **Adjust sensitivity** in game settings as needed
4. **Calibrate** if the game has calibration options

### Debug Mode

Send 'd' character via Serial Monitor (115200 baud) to display:
- Current joystick positions
- Button states
- Mapped values

## ⚙️ Configuration

Edit these constants in `ESP32_BT_Gamepad.ino`:

```cpp
#define DEADZONE       100   // Deadzone around center (0-500)
#define FILTER_ALPHA   0.3   // Smoothing factor (0.1-0.9)
                              // Lower = smoother, Higher = more responsive
```

### Calibration

If joysticks don't center properly:
1. Enable debug mode (send 'd' in Serial Monitor)
2. Note the center values when joysticks are at rest
3. Adjust `ADC_CENTER` constant (default: 2048)
4. Re-upload the code

## 🔍 Troubleshooting

### Connection Issues

**Bluetooth won't connect:**
- Restart ESP32 and PC Bluetooth
- Remove device from PC and re-pair
- Check Serial Monitor for error messages
- Ensure BleGamepad library is correctly installed

**Gamepad not recognized:**
- Check device manager / system settings
- Try a different USB port for ESP32
- Update Bluetooth drivers

### Joystick Issues

**Joystick drifting:**
- Increase `DEADZONE` value
- Calibrate joystick center position
- Check for loose connections

**Jerky movement:**
- Decrease `FILTER_ALPHA` for more smoothing
- Check power supply stability
- Verify all ground connections

**No joystick response:**
- Check wiring (especially VCC and GND)
- Verify GPIO pin assignments
- Test joystick module with multimeter

### Power Issues

**ESP32 resets randomly:**
- Use better power supply
- Check current capacity (min 500mA)
- Add capacitor across power rails

## 📊 Technical Specifications

- **Bluetooth**: BLE 4.2 / 5.0 (depending on ESP32 version)
- **Range**: Up to 10 meters (30 feet) line-of-sight
- **Latency**: ~10ms (100Hz update rate)
- **ADC Resolution**: 12-bit (4096 levels)
- **Axes**: 4 analog axes (X, Y, Z, RZ)
- **Buttons**: Up to 16 buttons supported
- **Power**: 3.3V @ ~100-200mA typical

## 🛠️ Advanced Customization

### Adding More Buttons

Add buttons to available GPIO pins and update the code:
```cpp
#define EXTRA_BTN_PIN 26
pinMode(EXTRA_BTN_PIN, INPUT_PULLUP);
// In loop():
if (digitalRead(EXTRA_BTN_PIN) == LOW) {
  bleGamepad.press(BUTTON_2);
} else {
  bleGamepad.release(BUTTON_2);
}
```

### Changing Controller Name

Edit line in code:
```cpp
BleGamepad bleGamepad("Your Custom Name", "Manufacturer", 100);
```

### Battery Operation

For portable use:
1. Connect 3.7V LiPo battery to ESP32 battery connector
2. Or use 5V power bank connected to USB port
3. Add power switch for convenience
4. Monitor battery voltage on ADC pin (voltage divider)

## 📝 License

This project is open source and available for personal and educational use.

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Report bugs
- Suggest features
- Submit pull requests
- Improve documentation

## 👨‍💻 Author

Created by NIKITH-14

## 📚 Resources

- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [BleGamepad Library](https://github.com/lemmingDev/ESP32-BLE-Gamepad)
- [Arduino ESP32 Guide](https://github.com/espressif/arduino-esp32)

## ⚠️ Disclaimer

This project is for educational purposes. Gaming performance may vary depending on your PC, game, and Bluetooth adapter quality. Always follow local regulations regarding wireless devices.

---

**Enjoy your wireless gaming experience! 🎮🚀**