# Bill of Materials (BOM) - ESP32 Bluetooth Game Controller

## Required Components

| # | Component | Quantity | Description | Est. Price (USD) | Where to Buy |
|---|-----------|----------|-------------|------------------|--------------|
| 1 | ESP32 Development Board | 1 | ESP32-WROOM-32 or ESP32-DevKitC | $5-8 | Amazon, AliExpress, Adafruit |
| 2 | Analog Joystick Module | 2 | KY-023 or similar dual-axis joystick | $2-3 each | Amazon, eBay, AliExpress |
| 3 | Push Button | 1 | 6mm tactile push button (optional) | $0.10 | Amazon, local electronics store |
| 4 | Breadboard | 1 | 400 or 830 tie-points | $2-5 | Amazon, Adafruit, SparkFun |
| 5 | Jumper Wires | 20+ | Male-to-male and male-to-female | $2-3 | Amazon, AliExpress |
| 6 | Micro USB Cable | 1 | For programming and power | $2-3 | Amazon, local store |

**Total Estimated Cost: $15-25 USD**

## Optional Components

| # | Component | Quantity | Description | Est. Price (USD) | Purpose |
|---|-----------|----------|-------------|------------------|---------|
| 1 | 3.7V LiPo Battery | 1 | 500-2000mAh with JST connector | $5-10 | Portable operation |
| 2 | Battery Charger Module | 1 | TP4056 USB charger board | $1-2 | Charging LiPo battery |
| 3 | Power Switch | 1 | SPST slide or toggle switch | $0.50 | Power on/off control |
| 4 | Enclosure/Case | 1 | 3D printed or plastic project box | $5-10 | Professional finish |
| 5 | Vibration Motor | 2 | Small DC vibration motors | $1-2 each | Haptic feedback (advanced) |
| 6 | LED Indicators | 2-3 | 3mm or 5mm LEDs with resistors | $0.20 each | Status indication |
| 7 | Heat Shrink Tubing | 1 set | Various sizes | $3-5 | Wire protection |
| 8 | 10kΩ Resistor | 3-5 | For pull-up/pull-down | $0.05 each | Button circuits |

## Component Details and Specifications

### 1. ESP32 Development Board

**Recommended Models:**
- ESP32-DevKitC V4 (most common)
- ESP32-WROOM-32
- NodeMCU-32S
- DOIT ESP32 DevKit v1

**Specifications:**
- CPU: Dual-core 240MHz
- Bluetooth: BLE 4.2 / 5.0
- WiFi: 802.11 b/g/n
- GPIO Pins: 30+
- ADC: 12-bit, multiple channels
- Power: 3.3V logic, 5V USB input
- Flash: 4MB minimum

**Features to Look For:**
- Built-in USB-to-Serial (CP2102 or CH340)
- Proper pin labels
- Reset and boot buttons
- Good reviews for Bluetooth stability

### 2. Analog Joystick Module

**Common Models:**
- KY-023 Joystick Module
- PS2 Style Joystick Module
- Sparkfun Analog Joystick

**Specifications:**
- Operating Voltage: 3.3V-5V
- X/Y Axis Output: 0-VCC analog voltage
- Button: Normally open, active LOW when pressed
- Mounting: PCB with mounting holes
- Shaft: Rubber or plastic cap

**Features to Look For:**
- 5-pin interface (VCC, GND, VRx, VRy, SW)
- Self-centering spring mechanism
- Smooth movement without dead spots
- Durable construction

### 3. Breadboard

**Recommended Sizes:**
- 400 tie-points: Compact, sufficient for this project
- 830 tie-points: More space for expansion

**Features:**
- Standard 2.54mm (0.1") pitch
- Multiple power rails
- Interlocking (for combining multiple)

### 4. Jumper Wires

**Types Needed:**
- Male-to-Male: For breadboard connections
- Male-to-Female: For connecting to ESP32/modules
- Female-to-Female: Optional, for module-to-module

**Recommended Set:**
- 20cm length
- Mixed colors for easy identification
- Pack of 40-120 wires

### 5. LiPo Battery (Optional)

**Specifications:**
- Voltage: 3.7V (single cell)
- Capacity: 500-2000mAh
- Connector: JST 2.0mm or compatible with ESP32
- Protection: Built-in over-charge/discharge protection

**Usage Notes:**
- Higher capacity = longer runtime
- 500mAh: ~2-3 hours
- 1000mAh: ~5-6 hours
- 2000mAh: ~10-12 hours

## Sourcing Options

### Online Retailers

**United States:**
- Amazon.com (fast shipping, higher prices)
- Adafruit.com (quality components, educational focus)
- SparkFun.com (excellent documentation)
- Mouser.com (professional components)
- Digi-Key.com (huge selection)

**International:**
- AliExpress.com (cheapest, slow shipping)
- Banggood.com (good prices, decent shipping)
- eBay.com (varies by seller)

**Local:**
- Electronics hobby stores
- Maker spaces
- University bookstores
- Radio Shack (if still available)

### Buying Tips

1. **Buy in Bundles:**
   - Many sellers offer ESP32 + sensor kits
   - Often cheaper than buying individually

2. **Check Shipping:**
   - Free shipping from China takes 2-4 weeks
   - Expedited shipping adds $5-15

3. **Read Reviews:**
   - Check for Bluetooth compatibility issues
   - Verify ESP32 board works with Arduino IDE

4. **Quality Considerations:**
   - Cheap joysticks may have poor centering
   - Good quality modules last longer
   - ESP32 boards are generally reliable regardless of price

## Assembly Cost Breakdown

### Minimal Setup (Breadboard)
```
ESP32 Board:        $6
2x Joysticks:       $4
Breadboard:         $3
Jumper Wires:       $2
USB Cable:          $2
─────────────────────
Total:             $17
```

### Recommended Setup (with Battery)
```
ESP32 Board:        $7
2x Joysticks:       $5
LiPo Battery:       $7
Charger Module:     $1
Breadboard:         $3
Jumper Wires:       $2
USB Cable:          $2
Switch:             $1
─────────────────────
Total:             $28
```

### Professional Setup (Enclosure)
```
ESP32 Board:        $7
2x Joysticks:       $6
LiPo Battery:       $8
Charger Module:     $2
Custom PCB:        $10
3D Printed Case:   $10
LEDs & Resistors:   $2
Misc Hardware:      $3
─────────────────────
Total:             $48
```

## Alternative Components

### Lower Cost Options

**ESP32 Alternatives:**
- ESP32-C3 (cheaper, single core, still has BLE)
- ESP32-S2 (no Bluetooth - NOT RECOMMENDED for this project)

**Joystick Alternatives:**
- Salvaged PS2/Xbox controller joysticks
- Potentiometers with custom gimbal
- Hall effect joysticks (more expensive but more durable)

### Higher Quality Options

**Premium Joysticks:**
- Adafruit Analog 2-axis Thumb Joystick
- SparkFun Joystick Breakout
- Xbox/PS5 replacement joystick modules

**Professional ESP32:**
- ESP32-WROVER (more RAM)
- ESP32-S3 (newer, faster)
- Industrial ESP32 modules

## Tools Required

### Basic Tools (Likely Already Have)
- None! This is a breadboard project
- Just need USB cable and computer

### Recommended Tools
- Wire strippers (if soldering later)
- Small screwdriver set
- Multimeter (for troubleshooting)
- Soldering iron (for permanent assembly)

### Advanced Tools
- 3D Printer (for custom enclosure)
- Hot glue gun (for strain relief)
- Helping hands (for soldering)
- Label maker (for professional look)

## Purchasing Checklist

Print this checklist when shopping:

- [ ] ESP32 Development Board (with USB-to-Serial)
- [ ] 2x Analog Joystick Modules (KY-023 or similar)
- [ ] Breadboard (400 or 830 tie-points)
- [ ] Jumper Wire Set (40+ wires, various types)
- [ ] Micro USB Cable (data + power)
- [ ] Optional: Push Button
- [ ] Optional: LiPo Battery (3.7V, 1000mAh+)
- [ ] Optional: TP4056 Charger Module
- [ ] Optional: Power Switch
- [ ] Optional: Enclosure/Project Box

## Storage and Organization

**Component Storage:**
- Use small plastic bins or compartment boxes
- Label each compartment
- Keep small parts (resistors, LEDs) in labeled bags
- Store in dry, cool place

**Cable Management:**
- Use twist ties or velcro straps
- Color-code by function
- Keep different wire types separate

---

**Ready to Build?**
1. Order components from your preferred supplier
2. While waiting, read the README.md and WIRING.md
3. Download and install Arduino IDE and libraries
4. Once parts arrive, follow the wiring guide
5. Upload the calibration sketch first
6. Then upload the main gamepad sketch
7. Enjoy gaming!

**Need Help?**
- Check the WIRING.md for connection diagrams
- See README.md for software setup
- Read GAME_SETUP.md for game-specific instructions
