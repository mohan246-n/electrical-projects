/*
  Digital Voltmeter — 0 to 25 V DC
  ---------------------------------
  Voltage divider (30k + 7.5k, ratio 5:1) scales the input
  down to the Arduino's 0-5 V ADC range. The reading is
  averaged for a steady display on a 16x2 I2C LCD.

  Wiring:
    Input+ : 30k - A0 - 7.5k - GND
    Input- : GND (common)
    LCD I2C: SDA A4, SCL A5 (Uno)
  Range: 0-25 V DC only. Never connect to AC mains.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---- Pin definitions ----
const int VOLTAGE_PIN = A0;  // Voltage divider output

// ---- Calibration ----
// Divider ratio: (30k + 7.5k) / 7.5k = 5.0. Adjust this after
// comparing with a multimeter (see README).
const float DIVIDER_RATIO = 5.0;
const float ADC_REF       = 5.0;  // Arduino ADC reference (V)
const int   SAMPLES       = 10;   // Readings to average

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change 0x27 to 0x3F if needed

float readVoltage() {
  long total = 0;
  for (int i = 0; i < SAMPLES; i++) {
    total += analogRead(VOLTAGE_PIN);
    delay(5);
  }
  float average = total / (float)SAMPLES;
  return (average * ADC_REF / 1023.0) * DIVIDER_RATIO;
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Digital Voltmeter");
  lcd.setCursor(0, 1);
  lcd.print("0-25V DC");
  delay(1500);
  lcd.clear();
  Serial.println("Digital Voltmeter ready.");
}

void loop() {
  float voltage = readVoltage();

  // LCD output.
  lcd.setCursor(0, 0);
  lcd.print("Voltage:      ");
  lcd.setCursor(0, 1);
  lcd.print(voltage, 2);
  lcd.print(" V DC    ");

  // Serial output.
  Serial.print("Voltage: ");
  Serial.print(voltage, 2);
  Serial.println(" V");

  delay(500);
}
