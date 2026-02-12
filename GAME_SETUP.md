# Game Setup Guide - ESP32 Bluetooth Racing Controller

This guide provides specific instructions for setting up the ESP32 Bluetooth Game Controller with popular racing games.

## General Setup Process

1. **Connect Controller**:
   - Power on ESP32 controller
   - Pair via Bluetooth settings
   - Verify connection in device manager/system settings

2. **Test Controller**:
   - Windows: Control Panel → Devices and Printers → Game Controller Settings
   - Linux: `jstest /dev/input/js0`
   - macOS: System Preferences → Bluetooth → verify "Connected"

3. **Launch Game**:
   - Start your racing game
   - Navigate to settings/options
   - Find controller or input configuration

## Racing Games Setup

### Asphalt 8/9 Airborne (PC)

**Controller Mapping:**
```
Steering:      Left Joystick X-axis
Accelerate:    Left Joystick Y-axis (Forward)
Brake:         Left Joystick Y-axis (Backward)
Nitro:         Left Joystick Button (Press)
Pause:         Right Joystick Button / Start Button
```

**Setup Steps:**
1. Launch Asphalt
2. Go to Settings → Controls
3. Select "Controller" mode
4. Choose "Manual" steering (for joystick control)
5. Test in quick race to verify controls
6. Adjust sensitivity if needed

**Recommended Settings:**
- Steering Sensitivity: 70-80%
- Acceleration Sensitivity: 80-90%
- Enable Manual Transmission (optional)

---

### Need for Speed: Heat / Payback

**Controller Mapping:**
```
Steering:      Left Joystick X-axis
Throttle:      Left Joystick Y-axis (Forward)
Brake:         Left Joystick Y-axis (Backward)
Nitrous:       Button 1 (Left Joystick Button)
Handbrake:     Button 2 (if configured)
Pause Menu:    Start Button (Right Joystick Button)
```

**Setup Steps:**
1. Go to Settings → Controls → Controller
2. Select "Advanced Controls"
3. Map controls:
   - Steer: Left Stick X
   - Gas: Left Stick Y+
   - Brake: Left Stick Y-
   - Nitrous: Button A/Cross
4. Save and test in free roam

**Tips:**
- Reduce steering sensitivity for better control
- Enable "Simulation" steering if available
- Adjust deadzone to prevent drift

---

### Forza Horizon 4/5

**Controller Mapping:**
```
Steering:      Left Joystick X-axis
Accelerate:    Left Joystick Y-axis (Forward)
Brake:         Left Joystick Y-axis (Backward)
E-Brake:       Left Joystick Button
Camera:        Right Joystick
Pause:         Start Button
```

**Setup Steps:**
1. Settings → Controls → Change Preset
2. Select "Custom" or create new preset
3. Configure:
   - Steering Axis: Left Stick Horizontal
   - Accelerate: Left Stick Vertical+
   - Brake: Left Stick Vertical-
   - Handbrake: Button A
4. Adjust advanced settings:
   - Steering linearity
   - Acceleration/deceleration linearity
   - Inside/outside deadzone

**Recommended Advanced Settings:**
- Steering Deadzone Inside: 0-5
- Steering Deadzone Outside: 95-100
- Steering Linearity: 50
- Acceleration Inside Deadzone: 0-5

---

### Project Cars 2/3

**Controller Mapping:**
```
Steering:      Left Joystick X-axis
Throttle:      Left Joystick Y-axis (Forward)
Brake:         Left Joystick Y-axis (Backward)
Clutch:        Button (if configured)
Look Around:   Right Joystick
Menu:          Start Button
```

**Setup Steps:**
1. Options → Controls → Edit Assignments
2. Select your controller from device list
3. Map each control individually
4. Configure Input Mode:
   - Choose "Analog" for joystick controls
5. Test in Practice mode

**Fine-Tuning:**
- Steering Sensitivity: 30-40 (this game is very sensitive)
- Speed Sensitivity: 50-60
- Controller Filtering: 50-70
- Force Feedback: 50-80 (if using rumble module)

---

### TrackMania (2020)

**Controller Mapping:**
```
Steering:      Left Joystick X-axis
Accelerate:    Left Joystick Y-axis (Forward)
Brake:         Left Joystick Y-axis (Backward)
Menu:          Start Button
```

**Setup Steps:**
1. Settings → Inputs
2. Select "Gamepad" preset
3. Customize bindings if needed
4. Adjust steering sensitivity
5. Test on practice track

**Tips:**
- TrackMania works great with analog controls
- Lower steering sensitivity for technical tracks
- Higher sensitivity for speed tracks

---

### F1 2021/2022

**Controller Mapping:**
```
Steering:      Left Joystick X-axis
Throttle:      Left Joystick Y-axis (Forward)
Brake:         Left Joystick Y-axis (Backward)
DRS:           Left Joystick Button
ERS Mode:      Button 2
Look Back:     Right Joystick Y-axis
Pause:         Start Button
```

**Setup Steps:**
1. Game Options → Settings → Controls
2. Select Controller Device
3. Choose "Custom" layout
4. Map all controls
5. Adjust steering:
   - Steering Saturation: 50-60
   - Steering Linearity: 20-30
   - Steering Deadzone: 5-10

---

## Troubleshooting Game-Specific Issues

### Controller Not Detected in Game

1. **Restart the game** after connecting controller
2. **Check game controller support**:
   - Some games require Xinput (Xbox) controller
   - Use controller emulation software if needed:
     - x360ce (Windows)
     - SDL2 Gamepad Tool (Linux)
3. **Update game** to latest version
4. **Verify in system**:
   - Windows: joy.cpl (Run → joy.cpl)
   - Test if system recognizes inputs

### Wrong Button Mappings

1. **Use game's remap feature** to manually assign buttons
2. **Check for controller profile** options
3. **Reset to default** and reconfigure
4. **Update controller firmware** (ESP32 code)

### Laggy or Unresponsive Controls

1. **Check Bluetooth connection quality**:
   - Reduce distance to PC
   - Remove interference sources
   - Use Bluetooth dongle instead of built-in
2. **Adjust filter settings** in ESP32 code:
   - Increase `FILTER_ALPHA` for faster response
3. **Lower game graphics settings** to improve overall performance
4. **Close background applications** using Bluetooth

### Steering Drift

1. **Calibrate joystick**:
   - Check center position
   - Adjust `ADC_CENTER` in code
2. **Increase deadzone**:
   - In game settings
   - In ESP32 code (`DEADZONE` constant)
3. **Check hardware**:
   - Ensure joystick is properly centered mechanically
   - Clean joystick contacts

## Controller Emulation Software

If games don't recognize the Bluetooth controller directly, use:

### Windows
- **x360ce** (Xbox 360 Controller Emulator)
  - Download from x360ce.com
  - Place in game folder
  - Configure ESP32 controller to emulate Xbox 360

- **DS4Windows** (DualShock 4 Emulator)
  - Can emulate PS4 controller
  - Better compatibility with some games

### Linux
- **xboxdrv** (Xbox Driver)
  ```bash
  sudo apt install xboxdrv
  xboxdrv --silent --type xbox360 --device-by-id [device-id]
  ```

- **SDL2 Gamepad Mapper**
  - Create custom mapping string
  - Export SDL_GAMECONTROLLERCONFIG

### macOS
- **Enjoyable** (Input Mapper)
  - Map controller inputs to keyboard/mouse
  - Good for games without gamepad support

## Steam Configuration

### Steam Input Support

1. **Open Steam Big Picture Mode**
2. **Settings → Controller Settings**
3. **Enable Generic Gamepad Configuration Support**
4. **Configure controller**:
   - Detect ESP32 controller
   - Create custom binding
   - Save configuration
5. **Per-game configuration**:
   - Library → Game → Manage → Controller Options
   - Choose custom binding

### Benefits of Steam Input
- Works with any game launched through Steam
- Advanced customization options
- Per-game configurations
- Community configurations available

## Performance Optimization Tips

1. **Reduce Latency**:
   - Use 5GHz WiFi band if possible (for PC)
   - Keep ESP32 close to PC (< 3 meters)
   - Update Bluetooth drivers

2. **Improve Smoothness**:
   - Adjust `FILTER_ALPHA` in code
   - Calibrate joystick center point
   - Use quality joystick modules

3. **Better Precision**:
   - Reduce in-game sensitivity
   - Increase deadzone for stability
   - Use simulation steering mode if available

4. **Battery Life** (if using battery):
   - Lower Bluetooth transmission power if supported
   - Reduce update rate (increase delay in loop)
   - Use sleep mode when idle

## Testing Tools

### Windows
- **joy.cpl**: Built-in gamepad tester
  - Run → joy.cpl → Properties
  - View all axes and buttons in real-time

- **Gamepad Tester**: Web-based tool
  - Visit: https://gamepad-tester.com
  - Test in browser

### Linux
- **jstest**: Command-line joystick tester
  ```bash
  jstest /dev/input/js0
  ```

- **jstest-gtk**: GUI joystick tester
  ```bash
  sudo apt install jstest-gtk
  jstest-gtk
  ```

### macOS
- **Joystick Show**: Simple joystick viewer app
- **Gamepad Tester**: Browser-based
- **SDL2 Controller Test**: If SDL2 is installed

## Additional Resources

- [PC Gaming Wiki](https://www.pcgamingwiki.com/) - Game-specific controller guides
- [Controller Compatibility List](https://github.com/lemmingDev/ESP32-BLE-Gamepad/wiki) - ESP32-BLE-Gamepad compatibility
- [Steam Community](https://steamcommunity.com/groups/SteamClientBeta/discussions/) - Controller configuration help

---

**Happy Racing! 🏎️💨**
