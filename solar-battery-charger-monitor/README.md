# Solar Battery Charger Monitor

Monitors a solar panel and a 12 V battery, displays voltages on a
16×2 LCD and the Serial Monitor, and disconnects the solar panel
from the battery (charge cutoff) when the battery is full — so the
battery is not overcharged.

## How it works

Two voltage dividers scale the panel voltage and the battery voltage
down to the Arduino's 0–5 V ADC range. The Arduino reads both,
converts them to real volts, and displays them. A relay between the
solar panel and the battery is ON (charging) while the battery is
below the full-charge voltage, and OFF (cutoff) once the battery
reaches it. Charging resumes when the battery drops below the
resume voltage (hysteresis, so the relay does not chatter).

## Components

| Component | Value / spec | Qty |
|-----------|--------------|-----|
| Arduino Uno | — | 1 |
| Solar panel | 12 V, 10–20 W | 1 |
| Battery | 12 V lead-acid | 1 |
| Relay module | 5 V, 1-channel | 1 |
| LCD | 16×2 with I2C backpack | 1 |
| Resistors | 30 kΩ and 7.5 kΩ per divider (panel + battery = 2 sets) | 4 |
| Fuse | 5 A, in series with the battery | 1 |
| Diode | 1N4007 (panel → relay, prevents back-feed) | 1 |
| Breadboard, jumper wires | — | — |

## Circuit diagram (text)

```
Solar panel + ── 1N4007 diode ── Relay COM
Relay NO ─────────────────────── Battery + (through 5A fuse)
Solar panel - ─────────────────── Battery - / Arduino GND (common)

Battery + ── 30k resistor ──┬── A1 (Arduino) ── 7.5k resistor ── GND
                            (battery voltage divider, ~5:1)
Solar panel + ── 30k ──┬── A0 ── 7.5k ── GND
                       (panel voltage divider, ~5:1)

Arduino D7 ── Relay IN1 (charging relay, active LOW)
Arduino SDA/SCL ── LCD I2C (SDA A4, SCL A5 on Uno)
```

Divider ratio: 30 kΩ + 7.5 kΩ gives a 5:1 ratio, so up to 25 V
reads as up to 5 V at the ADC. The relay is OFF (not charging)
on startup.

## Wiring steps

1. **Do the low-voltage divider and LCD wiring first, with the
   panel and battery disconnected.**
2. Build both dividers as shown; check each with a multimeter
   before connecting to the Arduino.
3. Connect the LCD I2C lines (SDA → A4, SCL → A5, VCC → 5 V,
   GND → GND).
4. Connect the relay: IN1 → D7, VCC → 5 V, GND → GND. Panel →
   diode → relay COM; relay NO → battery + through the 5 A fuse.
5. Connect battery − to Arduino GND (common ground).
6. Upload `solar-battery-charger-monitor.ino` and open the Serial
   Monitor (9600 baud). Reconnect the battery, then the panel.

## Calibration

Measure the real battery voltage with a multimeter and compare it
with the LCD reading. If it is off, adjust `DIVIDER_RATIO`
(default 5.0) in the code until they agree. Default cutoffs:
full charge 14.4 V, resume charging at 13.0 V — suitable for a
12 V lead-acid battery; change them for other battery types.

## Safety notes

- Reversed polarity will damage the Arduino and battery — check
  +/− with a multimeter before connecting.
- Use the 5 A fuse in series with the battery. Never short a
  12 V battery.
- This project is for DC only. Never connect it to AC mains.
- The charge cutoff is a simple relay cutoff, not a proper MPPT /
  charge controller — do not leave it unattended for long periods
  with a large panel.
