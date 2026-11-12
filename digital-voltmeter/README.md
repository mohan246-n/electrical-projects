# Digital Voltmeter

A simple DC voltmeter built with an Arduino and a 16×2 LCD.
It measures 0–25 V DC and displays the reading to two decimal
places.

## How it works

The voltage to be measured goes through a voltage divider
(30 kΩ + 7.5 kΩ, ratio 5:1), which scales it down to the
Arduino's 0–5 V ADC range. The Arduino reads the ADC value,
multiplies by the divider ratio to get the real voltage, and
prints it on the LCD and the Serial Monitor. Readings are
averaged over several samples to keep the display steady.

## Components

| Component | Value / spec | Qty |
|-----------|--------------|-----|
| Arduino Uno | — | 1 |
| LCD | 16×2 with I2C backpack | 1 |
| Resistors | 30 kΩ (R1) and 7.5 kΩ (R2) — 1% tolerance preferred | 2 |
| Test leads / screw terminal | for the voltage input | 1 |
| Breadboard, jumper wires | — | — |

## Circuit diagram (text)

```
Voltage to measure (+) ── 30k resistor (R1) ──┬── A0 (Arduino)
                                               │
                                               └── 7.5k resistor (R2) ── GND
Voltage to measure (-) ──────────────────────── GND (common)

Arduino SDA (A4) ── LCD SDA
Arduino SCL (A5) ── LCD SCL
Arduino 5V / GND ── LCD VCC / GND
```

Divider ratio = (R1 + R2) / R2 = (30 kΩ + 7.5 kΩ) / 7.5 kΩ = 5.
So 25 V in → 5 V at A0; 5 V in → 1 V at A0.

## Wiring steps

1. Build the divider on the breadboard: input + → 30 kΩ → A0
   node → 7.5 kΩ → GND.
2. Connect the input − to Arduino GND.
3. Connect the LCD: SDA → A4, SCL → A5, VCC → 5 V, GND → GND.
4. Upload `digital-voltmeter.ino`.
5. Apply a known voltage (e.g. a 9 V battery) and check the LCD.

## Calibration

1. Measure the real input voltage with a trusted multimeter.
2. Compare it with the LCD reading.
3. If they differ, adjust `DIVIDER_RATIO` (default 5.0) in the
   code — increase it if the LCD reads low, decrease it if it
   reads high — until they agree.
4. For best accuracy use 1% resistors, and measure your Arduino's
   actual 5 V rail and set `ADC_REF` to that value if it is not
   exactly 5.00 V.

## Safety notes

- **DC only, 0–25 V maximum.** Never connect to AC mains or to
  voltages above 25 V — that will damage the Arduino.
- Always connect the input − to Arduino GND first, then the input +.
- Do not measure the voltage of a circuit while it is connected
  to mains power.
