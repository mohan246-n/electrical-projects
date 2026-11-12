/*
  Solar Battery Charger Monitor
  ------------------------------
  Reads solar panel and 12 V battery voltage through voltage
  dividers, shows them on a 16x2 I2C LCD and Serial, and cuts
  off charging (relay OFF) when the battery is full.
  Relay is OFF (not charging) on startup (safe default).

  Wiring:
    Panel divider  : panel+ - 30k - A0 - 7.5k - GND
    Battery divider: batt+  - 30k - A1 - 7.5k - GND
    Charge relay   : D7 (active LOW)
    LCD I2C        : SDA A4, SCL A5 (Uno)
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---- Pin definitions ----
const int PANEL_PIN    = A0;  // Solar panel voltage divider
const int BATTERY_PIN  = A1;  // Battery voltage divider
const int RELAY_PIN    = 7;   // Charge relay (active LOW)

// ---- Calibration / thresholds ----
// Divider ratio: (30k + 7.5k) / 7.5k = 5.0. Adjust after
// comparing with a multimeter.
const float DIVIDER_RATIO = 5.0;
const float ADC_REF       = 5.0;  // Arduino ADC reference (V)

const float FULL_VOLTAGE   = 14.4;  // Stop charging at this battery voltage
const float RESUME_VOLTAGE = 13.0;  // Resume charging below this voltage

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change 0x27 to 0x3F if needed

bool charging = false;

float readVoltage(int pin) {
  int raw = analogRead(pin);
  return (raw * ADC_REF / 1023.0) * DIVIDER_RATIO;
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  // Safe default: relay OFF (not charging) on startup.
  digitalWrite(RELAY_PIN, HIGH);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Solar Monitor");
  delay(1000);
  lcd.clear();
  Serial.println("Solar Battery Charger Monitor ready.");
}

void loop() {
  float panelVoltage   = readVoltage(PANEL_PIN);
  float batteryVoltage = readVoltage(BATTERY_PIN);

  // Charge control with hysteresis.
  if (!charging && batteryVoltage < RESUME_VOLTAGE && panelVoltage > batteryVoltage) {
    charging = true;
    digitalWrite(RELAY_PIN, LOW);  // LOW = relay ON (charging)
    Serial.println("Charging ON");
  } else if (charging && batteryVoltage >= FULL_VOLTAGE) {
    charging = false;
    digitalWrite(RELAY_PIN, HIGH);  // HIGH = relay OFF (cutoff)
    Serial.println("Battery full - charging OFF (cutoff)");
  }

  // LCD output.
  lcd.setCursor(0, 0);
  lcd.print("P:");
  lcd.print(panelVoltage, 1);
  lcd.print("V B:");
  lcd.print(batteryVoltage, 1);
  lcd.print("V ");
  lcd.setCursor(0, 1);
  lcd.print(charging ? "CHARGING     " : "CUTOFF/FULL  ");

  // Serial output.
  Serial.print("Panel: ");
  Serial.print(panelVoltage, 2);
  Serial.print(" V | Battery: ");
  Serial.print(batteryVoltage, 2);
  Serial.print(" V | ");
  Serial.println(charging ? "CHARGING" : "NOT CHARGING");

  delay(1000);
}
