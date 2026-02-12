/*
 * ESP32 Joystick Calibration Tool
 * 
 * Use this sketch to calibrate your joystick modules before using the main gamepad sketch.
 * This will help you find the correct center values and ranges for your specific hardware.
 * 
 * Instructions:
 * 1. Upload this sketch to your ESP32
 * 2. Open Serial Monitor (115200 baud)
 * 3. Leave joysticks at center position for a few seconds
 * 4. Move each joystick to all corners and extremes
 * 5. Note the min, max, and center values displayed
 * 6. Update the main sketch with these values if needed
 */

// Pin Definitions (same as main sketch)
#define LEFT_JOY_X_PIN    34
#define LEFT_JOY_Y_PIN    35
#define LEFT_JOY_BTN_PIN  32

#define RIGHT_JOY_X_PIN   36
#define RIGHT_JOY_Y_PIN   39
#define RIGHT_JOY_BTN_PIN 33

#define PAUSE_BTN_PIN     25

// Calibration variables
int leftXMin = 4095, leftXMax = 0, leftXCenter = 0;
int leftYMin = 4095, leftYMax = 0, leftYCenter = 0;
int rightXMin = 4095, rightXMax = 0, rightXCenter = 0;
int rightYMin = 4095, rightYMax = 0, rightYCenter = 0;

int centerSamples = 0;
unsigned long centerStartTime = 0;
bool centeringMode = true;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\n\n");
  Serial.println("========================================");
  Serial.println("  ESP32 Joystick Calibration Tool");
  Serial.println("========================================");
  Serial.println();
  
  // Configure pins
  pinMode(LEFT_JOY_X_PIN, INPUT);
  pinMode(LEFT_JOY_Y_PIN, INPUT);
  pinMode(LEFT_JOY_BTN_PIN, INPUT_PULLUP);
  
  pinMode(RIGHT_JOY_X_PIN, INPUT);
  pinMode(RIGHT_JOY_Y_PIN, INPUT);
  pinMode(RIGHT_JOY_BTN_PIN, INPUT_PULLUP);
  
  pinMode(PAUSE_BTN_PIN, INPUT_PULLUP);
  
  Serial.println("STEP 1: Keep joysticks at CENTER position...");
  Serial.println("Sampling center values for 3 seconds...");
  Serial.println();
  
  centerStartTime = millis();
}

void loop() {
  // Read current values
  int leftX = analogRead(LEFT_JOY_X_PIN);
  int leftY = analogRead(LEFT_JOY_Y_PIN);
  int rightX = analogRead(RIGHT_JOY_X_PIN);
  int rightY = analogRead(RIGHT_JOY_Y_PIN);
  
  // Read buttons
  bool leftBtn = (digitalRead(LEFT_JOY_BTN_PIN) == LOW);
  bool rightBtn = (digitalRead(RIGHT_JOY_BTN_PIN) == LOW);
  bool pauseBtn = (digitalRead(PAUSE_BTN_PIN) == LOW);
  
  // Centering mode - sample center position
  if (centeringMode) {
    if (millis() - centerStartTime < 3000) {
      // Accumulate center values
      leftXCenter += leftX;
      leftYCenter += leftY;
      rightXCenter += rightX;
      rightYCenter += rightY;
      centerSamples++;
      
      // Show progress
      if (centerSamples % 10 == 0) {
        Serial.print(".");
      }
    } else {
      // Calculate average center values
      if (centerSamples > 0) {
        leftXCenter /= centerSamples;
        leftYCenter /= centerSamples;
        rightXCenter /= centerSamples;
        rightYCenter /= centerSamples;
      }
      
      Serial.println("\n");
      Serial.println("Center values captured!");
      Serial.println("----------------------------------------");
      Serial.println("Left Joystick Center:");
      Serial.print("  X-axis: "); Serial.println(leftXCenter);
      Serial.print("  Y-axis: "); Serial.println(leftYCenter);
      Serial.println("Right Joystick Center:");
      Serial.print("  X-axis: "); Serial.println(rightXCenter);
      Serial.print("  Y-axis: "); Serial.println(rightYCenter);
      Serial.println("----------------------------------------");
      Serial.println();
      Serial.println("STEP 2: Move joysticks to ALL extremes...");
      Serial.println("Move each stick in full circles and to all corners");
      Serial.println("Press any button when done (or wait 10 seconds)");
      Serial.println();
      
      centeringMode = false;
      centerStartTime = millis();
    }
    
    delay(10);
    return;
  }
  
  // Range detection mode - find min and max values
  leftXMin = min(leftXMin, leftX);
  leftXMax = max(leftXMax, leftX);
  leftYMin = min(leftYMin, leftY);
  leftYMax = max(leftYMax, leftY);
  rightXMin = min(rightXMin, rightX);
  rightXMax = max(rightXMax, rightX);
  rightYMin = min(rightYMin, rightY);
  rightYMax = max(rightYMax, rightY);
  
  // Display current values every 200ms
  static unsigned long lastDisplay = 0;
  if (millis() - lastDisplay > 200) {
    lastDisplay = millis();
    
    Serial.println("Current Values:");
    Serial.print("  Left  X: "); Serial.print(leftX);
    Serial.print(" ("); Serial.print(leftXMin); Serial.print("-"); Serial.print(leftXMax); Serial.println(")");
    
    Serial.print("  Left  Y: "); Serial.print(leftY);
    Serial.print(" ("); Serial.print(leftYMin); Serial.print("-"); Serial.print(leftYMax); Serial.println(")");
    
    Serial.print("  Right X: "); Serial.print(rightX);
    Serial.print(" ("); Serial.print(rightXMin); Serial.print("-"); Serial.print(rightXMax); Serial.println(")");
    
    Serial.print("  Right Y: "); Serial.print(rightY);
    Serial.print(" ("); Serial.print(rightYMin); Serial.print("-"); Serial.print(rightYMax); Serial.println(")");
    
    Serial.print("  Buttons: L="); Serial.print(leftBtn ? "ON" : "off");
    Serial.print(" R="); Serial.print(rightBtn ? "ON" : "off");
    Serial.print(" P="); Serial.println(pauseBtn ? "ON" : "off");
    Serial.println();
  }
  
  // Check if calibration is complete
  if (leftBtn || rightBtn || pauseBtn || (millis() - centerStartTime > 10000)) {
    delay(500); // Debounce
    
    // Display final calibration results
    Serial.println("\n\n");
    Serial.println("========================================");
    Serial.println("  CALIBRATION COMPLETE");
    Serial.println("========================================");
    Serial.println();
    
    Serial.println("Left Joystick:");
    Serial.println("----------------------------------------");
    Serial.print("  X-axis Min:    "); Serial.println(leftXMin);
    Serial.print("  X-axis Max:    "); Serial.println(leftXMax);
    Serial.print("  X-axis Center: "); Serial.println(leftXCenter);
    Serial.print("  X-axis Range:  "); Serial.println(leftXMax - leftXMin);
    Serial.println();
    Serial.print("  Y-axis Min:    "); Serial.println(leftYMin);
    Serial.print("  Y-axis Max:    "); Serial.println(leftYMax);
    Serial.print("  Y-axis Center: "); Serial.println(leftYCenter);
    Serial.print("  Y-axis Range:  "); Serial.println(leftYMax - leftYMin);
    Serial.println();
    
    Serial.println("Right Joystick:");
    Serial.println("----------------------------------------");
    Serial.print("  X-axis Min:    "); Serial.println(rightXMin);
    Serial.print("  X-axis Max:    "); Serial.println(rightXMax);
    Serial.print("  X-axis Center: "); Serial.println(rightXCenter);
    Serial.print("  X-axis Range:  "); Serial.println(rightXMax - rightXMin);
    Serial.println();
    Serial.print("  Y-axis Min:    "); Serial.println(rightYMin);
    Serial.print("  Y-axis Max:    "); Serial.println(rightYMax);
    Serial.print("  Y-axis Center: "); Serial.println(rightYCenter);
    Serial.print("  Y-axis Range:  "); Serial.println(rightYMax - rightYMin);
    Serial.println();
    
    // Provide recommendations
    Serial.println("RECOMMENDATIONS:");
    Serial.println("----------------------------------------");
    
    // Check if values look reasonable
    bool needsCalibration = false;
    
    if (abs(leftXCenter - 2048) > 200 || abs(leftYCenter - 2048) > 200 ||
        abs(rightXCenter - 2048) > 200 || abs(rightYCenter - 2048) > 200) {
      Serial.println("⚠ CENTER VALUES are not near 2048");
      Serial.println("  Update ADC_CENTER in main sketch:");
      int avgCenter = (leftXCenter + leftYCenter + rightXCenter + rightYCenter) / 4;
      Serial.print("  #define ADC_CENTER "); Serial.println(avgCenter);
      needsCalibration = true;
    } else {
      Serial.println("✓ Center values look good (near 2048)");
    }
    
    Serial.println();
    
    if (leftXMax < 3800 || leftYMax < 3800 || rightXMax < 3800 || rightYMax < 3800 ||
        leftXMin > 200 || leftYMin > 200 || rightXMin > 200 || rightYMin > 200) {
      Serial.println("⚠ RANGE VALUES are limited");
      Serial.println("  Your joysticks may not reach full range");
      Serial.println("  Check connections and power supply");
      needsCalibration = true;
    } else {
      Serial.println("✓ Range values look good (0-4095)");
    }
    
    Serial.println();
    
    if ((leftXMax - leftXMin) < 3000 || (leftYMax - leftYMin) < 3000 ||
        (rightXMax - rightXMin) < 3000 || (rightYMax - rightYMin) < 3000) {
      Serial.println("⚠ RANGE is too small");
      Serial.println("  Move joysticks more during calibration");
      Serial.println("  Or check for mechanical issues");
    } else {
      Serial.println("✓ Range is sufficient for gaming");
    }
    
    Serial.println();
    Serial.println("Suggested DEADZONE value:");
    int suggestedDeadzone = 100; // Default
    if ((leftXMax - leftXMin) < 3500) {
      suggestedDeadzone = 150;
    }
    Serial.print("  #define DEADZONE "); Serial.println(suggestedDeadzone);
    
    if (!needsCalibration) {
      Serial.println();
      Serial.println("✓ Your joysticks are properly calibrated!");
      Serial.println("  You can use the default values in the main sketch.");
    }
    
    Serial.println();
    Serial.println("========================================");
    Serial.println("  Calibration data saved above");
    Serial.println("  Press RESET button to calibrate again");
    Serial.println("========================================");
    
    // Stop here
    while (true) {
      delay(1000);
    }
  }
  
  delay(10);
}
