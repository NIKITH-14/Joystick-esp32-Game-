# Wiring Guide - ESP32 Bluetooth Game Controller

## Hardware Components Required

### Main Components
- 1x ESP32 Development Board (ESP32-WROOM-32 or similar)
- 2x Analog Joystick Modules (KY-023 or similar)
- 1x Push Button (for pause functionality)
- 1x 10kΩ Resistor (for push button pull-up, if not using internal pull-up)
- Breadboard and jumper wires
- USB cable for programming and power
- Optional: Battery pack for portable operation

### Joystick Module Specifications
- Operating Voltage: 3.3V - 5V
- Output: Analog voltage (0-3.3V on ESP32)
- Axes: X and Y analog outputs
- Button: Digital output (active LOW)

## Pin Connections

### Left Joystick (Steering and Speed Control)
```
Left Joystick Module    →    ESP32 Pin
─────────────────────────────────────
VCC                     →    3.3V
GND                     →    GND
VRx (X-axis)           →    GPIO 34 (ADC1_CH6)
VRy (Y-axis)           →    GPIO 35 (ADC1_CH7)
SW (Button)            →    GPIO 32
```

### Right Joystick (Additional Controls)
```
Right Joystick Module   →    ESP32 Pin
─────────────────────────────────────
VCC                     →    3.3V
GND                     →    GND
VRx (X-axis)           →    GPIO 36 (ADC1_CH0)
VRy (Y-axis)           →    GPIO 39 (ADC1_CH3)
SW (Button - Pause)    →    GPIO 33
```

### Additional Pause Button (Optional)
```
Pause Button            →    ESP32 Pin
─────────────────────────────────────
One terminal           →    GPIO 25
Other terminal         →    GND
```

## Circuit Diagram (Text Representation)

```
                                ESP32 Development Board
                        ┌─────────────────────────────────┐
                        │                                 │
    Left Joystick       │  GPIO 34 (ADC1_CH6) - Left X  │
    ┌──────────┐       │  GPIO 35 (ADC1_CH7) - Left Y  │
    │  VCC ────────────────  3.3V                      │
    │  GND ────────────────  GND                       │
    │  VRx ────────────────  GPIO 34                   │
    │  VRy ────────────────  GPIO 35                   │
    │  SW  ────────────────  GPIO 32                   │
    └──────────┘       │                                 │
                        │                                 │
    Right Joystick     │  GPIO 36 (ADC1_CH0) - Right X │
    ┌──────────┐       │  GPIO 39 (ADC1_CH3) - Right Y │
    │  VCC ────────────────  3.3V                      │
    │  GND ────────────────  GND                       │
    │  VRx ────────────────  GPIO 36                   │
    │  VRy ────────────────  GPIO 39                   │
    │  SW  ────────────────  GPIO 33                   │
    └──────────┘       │                                 │
                        │                                 │
    Pause Button       │  GPIO 25 - Pause Button       │
    ┌──────┐          │                                 │
    │  o───────────────────  GPIO 25                   │
    │  o───────────────────  GND                       │
    └──────┘          │                                 │
                        │                                 │
    USB Cable          │  USB - Programming & Power     │
    ──────────────────────  Micro USB Port              │
                        │                                 │
                        └─────────────────────────────────┘
```

## Important Notes

### ADC Pin Selection
The ESP32 has two ADC units. We use ADC1 pins because:
- ADC2 pins cannot be used when WiFi is active
- ADC1 pins (GPIO 32-39) are dedicated analog input pins
- Better stability and accuracy

### Recommended ADC1 Pins
- GPIO 32-39 are ADC1 channels
- Avoid GPIO 0, 2, 12, 15 (boot mode pins)
- GPIO 34-39 are input-only (no pull-up/pull-down)

### Power Considerations
1. **USB Power**: 
   - Connect ESP32 to PC via USB for programming and power
   - Sufficient for ESP32 and joystick modules
   
2. **Battery Power** (for portable use):
   - Use 3.7V LiPo battery with voltage regulator
   - Or use 5V power bank connected to USB
   - Ensure current capacity is at least 500mA

### Joystick Calibration
- Joystick center position should be around 2048 (mid-point of 0-4095)
- If joysticks are not centered, adjust the `ADC_CENTER` value in the code
- Use serial monitor to check raw ADC values for calibration

## Assembly Steps

1. **Connect Power Rails**
   - Connect ESP32 3.3V pin to breadboard positive rail
   - Connect ESP32 GND pin to breadboard negative rail

2. **Mount Left Joystick**
   - Place left joystick module on breadboard
   - Connect VCC to 3.3V rail
   - Connect GND to GND rail
   - Connect VRx to GPIO 34
   - Connect VRy to GPIO 35
   - Connect SW to GPIO 32

3. **Mount Right Joystick**
   - Place right joystick module on breadboard
   - Connect VCC to 3.3V rail
   - Connect GND to GND rail
   - Connect VRx to GPIO 36
   - Connect VRy to GPIO 39
   - Connect SW to GPIO 33

4. **Add Pause Button** (optional)
   - Connect one terminal to GPIO 25
   - Connect other terminal to GND
   - Internal pull-up resistor is used (INPUT_PULLUP)

5. **Verify Connections**
   - Double-check all power connections
   - Ensure no short circuits
   - Verify GPIO pin assignments

## Testing

1. **Power On**
   - Connect ESP32 to PC via USB
   - Check if power LED lights up

2. **Upload Code**
   - Open Arduino IDE
   - Select ESP32 board
   - Upload the ESP32_BT_Gamepad.ino sketch

3. **Check Serial Monitor**
   - Open Serial Monitor (115200 baud)
   - Check for "Starting ESP32 Bluetooth Game Controller..." message
   - Wait for "Bluetooth connected!" message

4. **Test Joysticks**
   - Move joysticks and verify smooth response
   - Press buttons and verify recognition
   - Send 'd' in serial monitor to see debug output

## Troubleshooting

### Joystick Not Responding
- Check power connections (VCC and GND)
- Verify ADC pin connections
- Check if joystick module is working (measure voltage output)

### Bluetooth Not Connecting
- Ensure BleGamepad library is installed
- Check if Bluetooth is enabled on PC
- Remove and re-pair the device
- Check ESP32 Bluetooth antenna is not obstructed

### Erratic Joystick Behavior
- Increase DEADZONE value in code
- Adjust FILTER_ALPHA for more/less smoothing
- Check for loose connections
- Ensure stable power supply

### Button Not Working
- Verify button connections
- Check if using correct GPIO pins
- Test button with multimeter for continuity
- Ensure INPUT_PULLUP is configured correctly
