# Troubleshooting Guide - ESP32 Bluetooth Game Controller

This guide helps you diagnose and fix common issues with the ESP32 Bluetooth Game Controller.

## Table of Contents
- [Hardware Issues](#hardware-issues)
- [Bluetooth Connection Issues](#bluetooth-connection-issues)
- [Joystick Problems](#joystick-problems)
- [Button Issues](#button-issues)
- [Software and Upload Issues](#software-and-upload-issues)
- [Performance Issues](#performance-issues)
- [Power Issues](#power-issues)

---

## Hardware Issues

### ESP32 Not Powering On

**Symptoms:**
- No LED on ESP32
- Computer doesn't detect device
- Nothing happens when connected

**Solutions:**
1. **Check USB cable:**
   - Use a data cable (not charge-only)
   - Try a different USB cable
   - Test cable with another device

2. **Check USB port:**
   - Try different USB ports on computer
   - Avoid USB hubs (use direct connection)
   - Check if port provides enough power (500mA min)

3. **Inspect ESP32 board:**
   - Look for physical damage
   - Check for loose components
   - Verify power LED is functional

### Joystick Module Not Responding

**Symptoms:**
- Joystick readings don't change
- All values show 0 or 4095
- No response to movement

**Solutions:**
1. **Check power connections:**
   ```
   VCC connected to 3.3V? ✓
   GND connected to GND?  ✓
   ```

2. **Verify signal connections:**
   - Check VRx and VRy pins are correctly connected
   - Ensure wires are firmly inserted
   - Test with multimeter (should read ~1.65V at center)

3. **Test joystick module:**
   - Upload calibration sketch
   - Monitor serial output
   - If no change when moving, module may be faulty

### Intermittent Connection

**Symptoms:**
- Connection drops randomly
- Erratic behavior
- Works sometimes, not always

**Solutions:**
1. **Check for loose wires:**
   - Press down all breadboard connections
   - Use shorter jumper wires
   - Consider soldering for permanent setup

2. **Power supply stability:**
   - Use USB port directly on computer
   - Avoid low-quality USB hubs
   - Check if power LED dims during operation

3. **Reduce electromagnetic interference:**
   - Keep away from WiFi routers
   - Avoid fluorescent lights
   - Don't place near motors or relays

---

## Bluetooth Connection Issues

### PC Can't Find ESP32 Controller

**Symptoms:**
- ESP32 not visible in Bluetooth device list
- Can't pair with PC

**Solutions:**
1. **Verify ESP32 is broadcasting:**
   - Open Serial Monitor (115200 baud)
   - Should see "Starting ESP32 Bluetooth Game Controller..."
   - Check for any error messages

2. **Check PC Bluetooth:**
   - Ensure Bluetooth is enabled
   - Update Bluetooth drivers
   - Try on different PC/laptop

3. **Reset Bluetooth stack:**
   - Restart ESP32 (press reset button)
   - Restart PC Bluetooth service
   - Remove all paired Bluetooth devices and retry

4. **Check code configuration:**
   ```cpp
   // Ensure BleGamepad is initialized correctly
   BleGamepad bleGamepad("ESP32 Racing Controller", "NIKITH", 100);
   ```

### Pairing Fails

**Symptoms:**
- Device visible but won't pair
- Pairing fails with error message
- Asks for PIN/passkey

**Solutions:**
1. **BLE doesn't require pairing:**
   - Just click "Connect" (not "Pair")
   - BLE devices often don't need pairing code
   - Try "Trust" on Linux

2. **Remove old pairing data:**
   - Remove device from Bluetooth settings
   - Restart ESP32
   - Restart computer
   - Try connecting fresh

3. **Update BleGamepad library:**
   - Check for latest version in Library Manager
   - Version 0.5.0 or higher recommended

### Connection Drops After a Few Seconds

**Symptoms:**
- Connects but disconnects quickly
- Connection unstable
- "Device disconnected" messages

**Solutions:**
1. **Check distance and obstacles:**
   - Keep ESP32 within 3 meters of PC
   - Remove metal objects between devices
   - Ensure line of sight

2. **Power issues:**
   - Use better USB power source
   - Add 100μF capacitor across power rails
   - Check if ESP32 is resetting (watch serial monitor)

3. **Bluetooth interference:**
   - Disable other Bluetooth devices
   - Move away from WiFi routers
   - Try different time of day (less interference)

4. **Update code:**
   ```cpp
   // Increase connection timeout
   bleGamepad.begin(&bleGamepadConfig);
   ```

---

## Joystick Problems

### Joystick Drifting (Auto-Movement)

**Symptoms:**
- Character/car moves without touching joystick
- Can't stay still
- Center position is off

**Solutions:**
1. **Increase deadzone:**
   ```cpp
   #define DEADZONE 150  // Increase from 100
   ```

2. **Calibrate center position:**
   - Run ESP32_Calibration.ino sketch
   - Note the center values
   - Update ADC_CENTER in main sketch:
   ```cpp
   #define ADC_CENTER 2100  // Adjust based on calibration
   ```

3. **Hardware fix:**
   - Clean joystick contacts
   - Check if physically centered when released
   - Replace faulty joystick module

### Jerky or Erratic Movement

**Symptoms:**
- Sudden jumps in position
- Not smooth
- Unpredictable behavior

**Solutions:**
1. **Increase filtering:**
   ```cpp
   #define FILTER_ALPHA 0.2  // Decrease from 0.3 for more smoothing
   ```

2. **Check power quality:**
   - Add 10μF capacitor near joystick VCC/GND
   - Use stable power source
   - Check for voltage drops

3. **Verify connections:**
   - Ensure solid connections
   - Keep wires short
   - Avoid running signal wires parallel to power wires

### Limited Range

**Symptoms:**
- Joystick doesn't reach full range
- Max values less than 4095
- Min values greater than 0

**Solutions:**
1. **Check voltage:**
   - Joystick should get 3.3V
   - Measure with multimeter
   - Verify power connections

2. **Physical limitation:**
   - Check if joystick mechanically limited
   - Remove any obstructions
   - Test with different joystick module

3. **Software mapping:**
   - Adjust mapping in code if needed
   - Use actual min/max from calibration

### One Axis Not Working

**Symptoms:**
- X-axis works but Y doesn't (or vice versa)
- One direction has no effect

**Solutions:**
1. **Check specific pin connection:**
   - Verify VRx or VRy is properly connected
   - Test continuity with multimeter
   - Swap wires to test if pin or module issue

2. **Test with calibration sketch:**
   - Upload ESP32_Calibration.ino
   - Check if values change for problematic axis
   - If no change, likely hardware issue

3. **GPIO pin selection:**
   - Ensure using ADC1 pins (GPIO 32-39)
   - Avoid GPIO 0, 2, 12, 15 (boot pins)
   - Try different GPIO pin

---

## Button Issues

### Button Not Recognized

**Symptoms:**
- Pressing button has no effect
- Button state always shows unpressed
- No response in games

**Solutions:**
1. **Check pull-up configuration:**
   ```cpp
   pinMode(BUTTON_PIN, INPUT_PULLUP);  // Ensure PULLUP is set
   
   // Button is active LOW
   if (digitalRead(BUTTON_PIN) == LOW) {
     // Button pressed
   }
   ```

2. **Test button hardware:**
   - Measure continuity when pressed
   - Check if button contacts are clean
   - Try different button

3. **Verify GPIO pin:**
   - Check wiring to correct pin
   - Ensure pin isn't already used
   - Try different GPIO pin

### Button Stuck or Always Active

**Symptoms:**
- Button appears always pressed
- Can't "unpress" button
- Game registers constant button press

**Solutions:**
1. **Check for short circuit:**
   - Ensure button pin not shorted to GND
   - Verify correct wiring
   - Check for solder bridges (if soldered)

2. **Logic inversion:**
   ```cpp
   // If using external pull-down instead of internal pull-up
   pinMode(BUTTON_PIN, INPUT);  // Not INPUT_PULLUP
   
   if (digitalRead(BUTTON_PIN) == HIGH) {  // Not LOW
     // Button pressed
   }
   ```

### Button Bouncing (Multiple Presses)

**Symptoms:**
- One press registers as multiple
- Inconsistent response
- Rapid on/off

**Solutions:**
1. **Add software debouncing:**
   ```cpp
   const int DEBOUNCE_MS = 50;
   static unsigned long lastPress = 0;
   
   if (digitalRead(BUTTON_PIN) == LOW) {
     if (millis() - lastPress > DEBOUNCE_MS) {
       // Button actually pressed
       lastPress = millis();
     }
   }
   ```

2. **Hardware debouncing:**
   - Add 0.1μF capacitor across button terminals
   - Use better quality button switches

---

## Software and Upload Issues

### "Board Not Found" or COM Port Issues

**Symptoms:**
- Can't upload sketch
- COM port not showing
- "Port doesn't exist" error

**Solutions:**
1. **Install USB drivers:**
   - CP210x driver for most ESP32 boards
   - CH340 driver for some clones
   - Restart computer after installing

2. **Manual port selection:**
   - Windows: Check Device Manager → Ports
   - Linux: `ls /dev/ttyUSB*` or `/dev/ttyACM*`
   - macOS: `ls /dev/cu.*`

3. **Linux permissions:**
   ```bash
   sudo usermod -a -G dialout $USER
   # Logout and login for changes to take effect
   ```

### Compilation Errors

**Symptoms:**
- Sketch won't compile
- Error messages about missing libraries
- "BleGamepad.h not found"

**Solutions:**
1. **Install required libraries:**
   - Arduino IDE → Sketch → Include Library → Manage Libraries
   - Search "ESP32-BLE-Gamepad"
   - Install by lemmingDev

2. **Install ESP32 board support:**
   - File → Preferences → Additional Board Manager URLs
   - Add: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Tools → Board → Boards Manager → Install "esp32"

3. **Check board selection:**
   - Tools → Board → ESP32 Arduino → ESP32 Dev Module
   - Tools → Upload Speed → 115200
   - Tools → Flash Frequency → 80MHz

### Upload Fails

**Symptoms:**
- Compilation succeeds but upload fails
- "Failed to connect" error
- Stuck at "Connecting..."

**Solutions:**
1. **Hold BOOT button:**
   - Press and hold BOOT button on ESP32
   - Click upload
   - Release when "Connecting..." changes to uploading

2. **Check upload settings:**
   ```
   Tools → Upload Speed → Try 115200 (slower but more reliable)
   Tools → Flash Mode → DIO
   Tools → Partition Scheme → Default
   ```

3. **Close Serial Monitor:**
   - Serial Monitor must be closed during upload
   - Close any other serial programs

---

## Performance Issues

### High Latency / Lag

**Symptoms:**
- Delayed response to inputs
- Noticeable lag in games
- Slow to respond

**Solutions:**
1. **Reduce filtering:**
   ```cpp
   #define FILTER_ALPHA 0.5  // Increase for faster response
   ```

2. **Increase update rate:**
   ```cpp
   delay(5);  // Change from 10 to 5 for 200Hz update rate
   ```

3. **Check Bluetooth distance:**
   - Keep ESP32 close to PC (< 2 meters)
   - Remove obstacles
   - Use external Bluetooth dongle if built-in is weak

### Game Doesn't Recognize Controller

**Symptoms:**
- Controller connected but game doesn't respond
- Game shows "No controller"
- Inputs not working in game

**Solutions:**
1. **Verify system recognition:**
   - Windows: Run `joy.cpl` to test
   - Linux: Run `jstest /dev/input/js0`
   - Should see inputs changing

2. **Game configuration:**
   - Check game controller settings
   - Manually map buttons/axes
   - Some games need controller enabled in settings

3. **Use compatibility layer:**
   - Try x360ce (Windows)
   - Steam Input (for Steam games)
   - DS4Windows (for DualShock emulation)

### Inconsistent Behavior

**Symptoms:**
- Sometimes works, sometimes doesn't
- Random disconnections
- Unpredictable responses

**Solutions:**
1. **Check power quality:**
   - Use high-quality USB cable
   - Try different power source
   - Add bulk capacitor (100μF) to power

2. **Monitor serial output:**
   - Watch for error messages
   - Check for ESP32 resets
   - Look for Bluetooth stack errors

3. **Update firmware:**
   - Get latest ESP32-BLE-Gamepad library
   - Update ESP32 board package
   - Re-upload sketch

---

## Power Issues

### ESP32 Resets Randomly

**Symptoms:**
- ESP32 restarts unexpectedly
- Serial shows restart messages
- Connection drops then reconnects

**Solutions:**
1. **Improve power supply:**
   - Use USB port directly on computer
   - Try different USB port/cable
   - Use powered USB hub

2. **Add capacitors:**
   - 100μF electrolytic across ESP32 power pins
   - 0.1μF ceramic capacitor near ESP32
   - Reduces voltage spikes

3. **Reduce power consumption:**
   ```cpp
   // Lower CPU frequency
   setCpuFrequencyMhz(160);  // Instead of 240MHz
   ```

### Battery Drains Quickly

**Symptoms:**
- Battery only lasts short time
- Rapid discharge
- Unexpectedly powers off

**Solutions:**
1. **Reduce update rate:**
   ```cpp
   delay(20);  // 50Hz instead of 100Hz
   ```

2. **Disable WiFi:**
   ```cpp
   #include <esp_wifi.h>
   
   void setup() {
     esp_wifi_stop();  // WiFi not needed for BLE
   }
   ```

3. **Power management:**
   - Use larger battery (1000mAh+)
   - Add deep sleep when idle
   - Lower Bluetooth transmission power

---

## Advanced Diagnostics

### Check ADC Values

```cpp
void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("L_X:"); Serial.print(analogRead(34));
  Serial.print(" L_Y:"); Serial.print(analogRead(35));
  Serial.print(" R_X:"); Serial.print(analogRead(36));
  Serial.print(" R_Y:"); Serial.println(analogRead(39));
  delay(100);
}
```

### Check Bluetooth Status

```cpp
void loop() {
  Serial.print("BT Connected: ");
  Serial.println(bleGamepad.isConnected() ? "YES" : "NO");
  delay(1000);
}
```

### Memory Check

```cpp
void printMemory() {
  Serial.print("Free heap: ");
  Serial.println(ESP.getFreeHeap());
}
```

---

## Getting Help

If you've tried everything and still have issues:

1. **Gather information:**
   - ESP32 board model
   - Arduino IDE version
   - Library versions
   - Serial Monitor output
   - Photo of wiring

2. **Check existing issues:**
   - GitHub repository issues
   - ESP32-BLE-Gamepad library issues

3. **Create detailed report:**
   - Describe problem clearly
   - Include error messages
   - Share code modifications
   - Provide serial output

4. **Community resources:**
   - Arduino Forums
   - ESP32 subreddit
   - Electronics Stack Exchange

---

**Still stuck?** Double-check the [WIRING.md](WIRING.md) guide and [README.md](README.md) for setup instructions.
