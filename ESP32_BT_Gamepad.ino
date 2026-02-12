/*
 * ESP32 Bluetooth Game Controller
 * 
 * A wireless Bluetooth HID gamepad using ESP32 and dual analog joysticks
 * Designed for PC racing games like Asphalt
 * 
 * Hardware:
 * - ESP32 Development Board
 * - 2x Analog Joystick Modules (with push buttons)
 * - Push button for pause functionality
 * 
 * Features:
 * - Left Joystick X-axis: Steering control
 * - Left Joystick Y-axis: Speed control (throttle/brake)
 * - Right Joystick or Button: Pause/Menu
 * - Bluetooth HID Gamepad profile for PC compatibility
 */

#include <BleGamepad.h>

// Pin Definitions
#define LEFT_JOY_X_PIN    34  // Left joystick X-axis (Steering)
#define LEFT_JOY_Y_PIN    35  // Left joystick Y-axis (Speed)
#define LEFT_JOY_BTN_PIN  32  // Left joystick button

#define RIGHT_JOY_X_PIN   36  // Right joystick X-axis
#define RIGHT_JOY_Y_PIN   39  // Right joystick Y-axis
#define RIGHT_JOY_BTN_PIN 33  // Right joystick button (Pause)

#define PAUSE_BTN_PIN     25  // Additional pause button

// Joystick Configuration
#define ADC_MAX           4095  // 12-bit ADC resolution
#define ADC_CENTER        2048  // Center position
#define DEADZONE          100   // Deadzone around center
#define FILTER_ALPHA      0.3   // Exponential moving average filter (0-1)

// Game Controller Configuration
BleGamepad bleGamepad("ESP32 Racing Controller", "NIKITH", 100);

// Smoothing variables
float leftXFiltered = ADC_CENTER;
float leftYFiltered = ADC_CENTER;
float rightXFiltered = ADC_CENTER;
float rightYFiltered = ADC_CENTER;

// Button states
bool leftBtnPressed = false;
bool rightBtnPressed = false;
bool pauseBtnPressed = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting ESP32 Bluetooth Game Controller...");
  
  // Configure analog input pins
  pinMode(LEFT_JOY_X_PIN, INPUT);
  pinMode(LEFT_JOY_Y_PIN, INPUT);
  pinMode(LEFT_JOY_BTN_PIN, INPUT_PULLUP);
  
  pinMode(RIGHT_JOY_X_PIN, INPUT);
  pinMode(RIGHT_JOY_Y_PIN, INPUT);
  pinMode(RIGHT_JOY_BTN_PIN, INPUT_PULLUP);
  
  pinMode(PAUSE_BTN_PIN, INPUT_PULLUP);
  
  // Configure BLE Gamepad
  bleGamepad.begin();
  
  // Wait for connection
  Serial.println("Waiting for Bluetooth connection...");
  while (!bleGamepad.isConnected()) {
    delay(100);
  }
  
  Serial.println("Bluetooth connected!");
  
  // Initialize filtered values
  leftXFiltered = analogRead(LEFT_JOY_X_PIN);
  leftYFiltered = analogRead(LEFT_JOY_Y_PIN);
  rightXFiltered = analogRead(RIGHT_JOY_X_PIN);
  rightYFiltered = analogRead(RIGHT_JOY_Y_PIN);
}

void loop() {
  if (bleGamepad.isConnected()) {
    // Read and filter joystick values
    readAndFilterJoysticks();
    
    // Read button states
    readButtons();
    
    // Map joystick values to gamepad range (-32767 to 32767)
    int16_t steeringValue = mapWithDeadzone(leftXFiltered, -32767, 32767);
    int16_t speedValue = mapWithDeadzone(leftYFiltered, -32767, 32767);
    int16_t rightXValue = mapWithDeadzone(rightXFiltered, -32767, 32767);
    int16_t rightYValue = mapWithDeadzone(rightYFiltered, -32767, 32767);
    
    // Set gamepad axes
    bleGamepad.setX(steeringValue);     // Steering (Left X-axis)
    bleGamepad.setY(speedValue);        // Speed (Left Y-axis)
    bleGamepad.setZ(rightXValue);       // Right joystick X
    bleGamepad.setRZ(rightYValue);      // Right joystick Y
    
    // Handle buttons
    if (leftBtnPressed) {
      bleGamepad.press(BUTTON_1);
    } else {
      bleGamepad.release(BUTTON_1);
    }
    
    // Pause functionality (right joystick button or dedicated pause button)
    if (rightBtnPressed || pauseBtnPressed) {
      bleGamepad.press(BUTTON_9);  // Start button (typically used for pause)
    } else {
      bleGamepad.release(BUTTON_9);
    }
    
    // Send the gamepad report
    bleGamepad.sendReport();
    
    // Debug output (optional)
    if (Serial.available() > 0 && Serial.read() == 'd') {
      printDebugInfo(steeringValue, speedValue, rightXValue, rightYValue);
    }
    
    delay(10); // Update rate: ~100Hz
  } else {
    Serial.println("Waiting for connection...");
    delay(1000);
  }
}

void readAndFilterJoysticks() {
  // Read raw analog values
  float leftXRaw = analogRead(LEFT_JOY_X_PIN);
  float leftYRaw = analogRead(LEFT_JOY_Y_PIN);
  float rightXRaw = analogRead(RIGHT_JOY_X_PIN);
  float rightYRaw = analogRead(RIGHT_JOY_Y_PIN);
  
  // Apply exponential moving average filter for smooth response
  leftXFiltered = (FILTER_ALPHA * leftXRaw) + ((1.0 - FILTER_ALPHA) * leftXFiltered);
  leftYFiltered = (FILTER_ALPHA * leftYRaw) + ((1.0 - FILTER_ALPHA) * leftYFiltered);
  rightXFiltered = (FILTER_ALPHA * rightXRaw) + ((1.0 - FILTER_ALPHA) * rightXFiltered);
  rightYFiltered = (FILTER_ALPHA * rightYRaw) + ((1.0 - FILTER_ALPHA) * rightYFiltered);
}

void readButtons() {
  // Active LOW buttons (using INPUT_PULLUP)
  leftBtnPressed = (digitalRead(LEFT_JOY_BTN_PIN) == LOW);
  rightBtnPressed = (digitalRead(RIGHT_JOY_BTN_PIN) == LOW);
  pauseBtnPressed = (digitalRead(PAUSE_BTN_PIN) == LOW);
}

int16_t mapWithDeadzone(float value, int16_t outputMin, int16_t outputMax) {
  // Calculate deviation from center
  float deviation = value - ADC_CENTER;
  
  // Apply deadzone
  if (abs(deviation) < DEADZONE) {
    return 0; // Center position
  }
  
  // Remove deadzone from the range and map to output range
  if (deviation > 0) {
    // Positive direction
    float adjustedValue = map(value, ADC_CENTER + DEADZONE, ADC_MAX, 0, outputMax);
    return constrain(adjustedValue, 0, outputMax);
  } else {
    // Negative direction
    float adjustedValue = map(value, 0, ADC_CENTER - DEADZONE, outputMin, 0);
    return constrain(adjustedValue, outputMin, 0);
  }
}

void printDebugInfo(int16_t steering, int16_t speed, int16_t rightX, int16_t rightY) {
  Serial.println("=== Gamepad Status ===");
  Serial.print("Steering (X): "); Serial.println(steering);
  Serial.print("Speed (Y): "); Serial.println(speed);
  Serial.print("Right X: "); Serial.println(rightX);
  Serial.print("Right Y: "); Serial.println(rightY);
  Serial.print("Left Btn: "); Serial.println(leftBtnPressed ? "PRESSED" : "Released");
  Serial.print("Pause Btn: "); Serial.println((rightBtnPressed || pauseBtnPressed) ? "PRESSED" : "Released");
  Serial.println("=====================");
}
