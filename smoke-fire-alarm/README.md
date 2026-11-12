# Smoke / Fire Alarm

An MQ-2 smoke sensor watches the air; when smoke rises above a
set threshold, a buzzer sounds and an LED flashes until the air
clears.

## How it works

The MQ-2 sensor's analog output rises with smoke / combustible
gas concentration. The Arduino reads it continuously and compares
it with a threshold. Above the threshold it turns on the buzzer
and flashes the alarm LED, and prints a warning on the Serial
Monitor. Below the threshold (with a lower switch-off level, so
it does not flicker on and off) the alarm stops. The sensor needs
about 1–2 minutes of warm-up after power-on before its readings
are stable.

## Components

| Component | Value / spec | Qty |
|-----------|--------------|-----|
| Arduino Uno | — | 1 |
| MQ-2 smoke / gas sensor module | with analog + digital output | 1 |
| Buzzer | 5 V active buzzer | 1 |
| LED | 5 mm red | 1 |
| Resistor | 220 Ω (LED) | 1 |
| Breadboard, jumper wires | — | — |

## Circuit diagram (text)

```
MQ-2 VCC ── Arduino 5V
MQ-2 GND ── Arduino GND
MQ-2 A0 ─── Arduino A0 (analog smoke level)
MQ-2 D0 ─── (not used)

Arduino D8 ── Buzzer + (buzzer - to GND)
Arduino D13 ── 220Ω ── Red LED ── GND
```

The buzzer and LED are OFF on startup.

## Wiring steps

1. Connect the MQ-2 module: VCC → 5 V, GND → GND, A0 → A0.
2. Connect the buzzer: + → D8, − → GND.
3. Connect the red LED: D13 → 220 Ω → LED anode, LED cathode → GND.
4. Upload `smoke-fire-alarm.ino`.
5. Power on and wait 1–2 minutes for the sensor to warm up and
   the baseline reading to settle (watch the Serial Monitor).
6. Test with a small, controlled smoke source (e.g. a blown-out
   match held nearby, in a ventilated area) — the buzzer should
   sound and the LED flash.

## Calibration

Note the baseline analog reading in clean air from the Serial
Monitor (typically 100–300). Set `ALARM_THRESHOLD` in the code
well above the baseline (default 400) and `CLEAR_THRESHOLD`
(default 350) below it, so normal cooking fumes do not set it
off but real smoke does. If it alarms too easily, raise the
threshold; if it misses smoke, lower it.

## Safety notes

- This is a learning / warning device, **not a certified fire
  alarm**. Do not rely on it as your only smoke alarm — install
  certified smoke alarms in your home.
- The MQ-2 gets warm in normal use — that is expected.
- Test with smoke only in a ventilated area, away from
  flammable materials, and never leave a test flame unattended.
- If the alarm sounds for real, leave the building and call
  emergency services — do not stay to investigate.
