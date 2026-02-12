# ESP32 Bluetooth Game Controller - Examples

This directory contains example sketches and code snippets for various use cases.

## Available Examples

### 1. ESP32_BT_Gamepad.ino (Main Sketch)
The primary sketch for the Bluetooth game controller with full functionality:
- Dual joystick support
- Bluetooth HID gamepad
- Smooth input filtering
- Button handling
- Configurable deadzone

**Use this for:** Complete racing game controller functionality

---

### 2. ESP32_Calibration.ino
A diagnostic and calibration tool to help you set up your joysticks correctly:
- Measures center positions
- Determines min/max ranges
- Tests button functionality
- Provides calibration recommendations

**Use this for:** Initial setup and troubleshooting

---

## Quick Start Examples

### Example 1: Basic Joystick Reading

```cpp
// Simple joystick reading without Bluetooth
#define JOY_X_PIN 34
#define JOY_Y_PIN 35

void setup() {
  Serial.begin(115200);
  pinMode(JOY_X_PIN, INPUT);
  pinMode(JOY_Y_PIN, INPUT);
}

void loop() {
  int xValue = analogRead(JOY_X_PIN);
  int yValue = analogRead(JOY_Y_PIN);
  
  Serial.print("X: "); Serial.print(xValue);
  Serial.print(" Y: "); Serial.println(yValue);
  
  delay(100);
}
```

### Example 2: Single Joystick Bluetooth Controller

```cpp
#include <BleGamepad.h>

#define JOY_X_PIN 34
#define JOY_Y_PIN 35

BleGamepad bleGamepad;

void setup() {
  Serial.begin(115200);
  bleGamepad.begin();
  pinMode(JOY_X_PIN, INPUT);
  pinMode(JOY_Y_PIN, INPUT);
}

void loop() {
  if (bleGamepad.isConnected()) {
    int x = analogRead(JOY_X_PIN);
    int y = analogRead(JOY_Y_PIN);
    
    // Map to gamepad range (-32767 to 32767)
    int16_t xMapped = map(x, 0, 4095, -32767, 32767);
    int16_t yMapped = map(y, 0, 4095, -32767, 32767);
    
    bleGamepad.setX(xMapped);
    bleGamepad.setY(yMapped);
    bleGamepad.sendReport();
    
    delay(10);
  }
}
```

### Example 3: Button Handling

```cpp
#include <BleGamepad.h>

#define BUTTON_A_PIN 32
#define BUTTON_B_PIN 33

BleGamepad bleGamepad;

void setup() {
  bleGamepad.begin();
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
}

void loop() {
  if (bleGamepad.isConnected()) {
    // Buttons are active LOW with INPUT_PULLUP
    if (digitalRead(BUTTON_A_PIN) == LOW) {
      bleGamepad.press(BUTTON_1);
    } else {
      bleGamepad.release(BUTTON_1);
    }
    
    if (digitalRead(BUTTON_B_PIN) == LOW) {
      bleGamepad.press(BUTTON_2);
    } else {
      bleGamepad.release(BUTTON_2);
    }
    
    delay(10);
  }
}
```

### Example 4: Smooth Input with Filtering

```cpp
#define FILTER_ALPHA 0.3  // Smoothing factor (0-1)

float filteredValue = 2048;  // Start at center

void loop() {
  float rawValue = analogRead(JOY_X_PIN);
  
  // Apply exponential moving average filter
  filteredValue = (FILTER_ALPHA * rawValue) + 
                  ((1.0 - FILTER_ALPHA) * filteredValue);
  
  // Use filteredValue for smoother control
  int16_t output = map((int)filteredValue, 0, 4095, -32767, 32767);
  
  // Send to gamepad...
}
```

### Example 5: Deadzone Implementation

```cpp
int16_t applyDeadzone(int value, int center, int deadzone) {
  int deviation = value - center;
  
  // If within deadzone, return center (0)
  if (abs(deviation) < deadzone) {
    return 0;
  }
  
  // Map outside deadzone to full range
  if (deviation > 0) {
    return map(value, center + deadzone, 4095, 0, 32767);
  } else {
    return map(value, 0, center - deadzone, -32767, 0);
  }
}
```

### Example 6: Multiple Button Configuration

```cpp
// Define all buttons
const int buttons[] = {32, 33, 25, 26, 27};
const int buttonCount = 5;

void setup() {
  bleGamepad.begin();
  
  // Initialize all buttons with pull-up
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void loop() {
  if (bleGamepad.isConnected()) {
    // Check each button
    for (int i = 0; i < buttonCount; i++) {
      if (digitalRead(buttons[i]) == LOW) {
        bleGamepad.press(i + 1);  // Button 1, 2, 3, etc.
      } else {
        bleGamepad.release(i + 1);
      }
    }
    
    delay(10);
  }
}
```

## Advanced Examples

### Example 7: Battery Level Monitoring

```cpp
#define BATTERY_PIN 36  // ADC pin for battery voltage
#define BATTERY_DIVIDER 2  // Voltage divider ratio

void setup() {
  pinMode(BATTERY_PIN, INPUT);
}

int getBatteryPercentage() {
  int rawValue = analogRead(BATTERY_PIN);
  float voltage = (rawValue / 4095.0) * 3.3 * BATTERY_DIVIDER;
  
  // LiPo battery: 4.2V (full) to 3.0V (empty)
  if (voltage >= 4.2) return 100;
  if (voltage <= 3.0) return 0;
  
  return (int)((voltage - 3.0) / 1.2 * 100);
}

void loop() {
  static unsigned long lastCheck = 0;
  
  if (millis() - lastCheck > 60000) {  // Check every minute
    int batteryLevel = getBatteryPercentage();
    Serial.print("Battery: ");
    Serial.print(batteryLevel);
    Serial.println("%");
    
    lastCheck = millis();
  }
}
```

### Example 8: LED Status Indicators

```cpp
#define LED_CONNECTED 2   // Green LED for connection status
#define LED_BATTERY 4     // Red LED for low battery

void setup() {
  pinMode(LED_CONNECTED, OUTPUT);
  pinMode(LED_BATTERY, OUTPUT);
}

void updateLEDs() {
  // Connection status
  digitalWrite(LED_CONNECTED, bleGamepad.isConnected() ? HIGH : LOW);
  
  // Battery status (blink if low)
  static unsigned long lastBlink = 0;
  static bool blinkState = false;
  
  if (getBatteryPercentage() < 20) {
    if (millis() - lastBlink > 500) {
      blinkState = !blinkState;
      digitalWrite(LED_BATTERY, blinkState ? HIGH : LOW);
      lastBlink = millis();
    }
  } else {
    digitalWrite(LED_BATTERY, LOW);
  }
}
```

### Example 9: Configurable Controller Name

```cpp
#include <Preferences.h>

Preferences preferences;

void setup() {
  preferences.begin("gamepad", false);
  
  // Read saved name or use default
  String name = preferences.getString("name", "ESP32 Controller");
  
  BleGamepad bleGamepad(name.c_str(), "NIKITH", 100);
  bleGamepad.begin();
}

void setControllerName(String newName) {
  preferences.putString("name", newName);
  // Restart required for name change to take effect
}
```

### Example 10: Power Saving Mode

```cpp
#include <esp_bt.h>
#include <esp_wifi.h>

void enablePowerSaving() {
  // Disable WiFi to save power
  esp_wifi_stop();
  
  // Reduce Bluetooth power
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_N12);
  
  // Reduce CPU frequency
  setCpuFrequencyMhz(80);  // Instead of 240MHz
}

void setup() {
  enablePowerSaving();
  bleGamepad.begin();
}
```

## Testing Your Controller

### Windows Game Controller Test
1. Press `Win + R`
2. Type `joy.cpl`
3. Press Enter
4. Select your controller and click "Properties"

### Linux Command Line Test
```bash
# List available joysticks
ls /dev/input/js*

# Test joystick
jstest /dev/input/js0
```

### Web-Based Test
Open in browser: https://gamepad-tester.com

## Common Modifications

### Change Update Rate
```cpp
// In loop() function
delay(10);  // 100Hz update rate

// Change to:
delay(20);  // 50Hz - better battery life
delay(5);   // 200Hz - lower latency
```

### Adjust Sensitivity
```cpp
// Less sensitive (more stable)
#define FILTER_ALPHA 0.2

// More responsive
#define FILTER_ALPHA 0.5
```

### Increase Deadzone
```cpp
// For drifting joysticks
#define DEADZONE 200  // Larger deadzone

// For precise joysticks
#define DEADZONE 50   // Smaller deadzone
```

## Troubleshooting Examples

See the main README.md for detailed troubleshooting steps.

## Contributing Your Examples

If you create a useful example or modification, please consider contributing it back to the project!

1. Create a new .ino file with your example
2. Add documentation explaining what it does
3. Submit a pull request

---

**More Questions?**
- Check the main [README.md](README.md) for general information
- See [WIRING.md](WIRING.md) for hardware setup
- Read [GAME_SETUP.md](GAME_SETUP.md) for game-specific configuration
