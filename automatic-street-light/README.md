# Automatic Street Light

A street light that switches itself on at dusk and off at dawn, using
an LDR (light-dependent resistor) to sense ambient light and a relay
to switch the lamp.

## How it works

The LDR and a fixed resistor form a voltage divider. In daylight the
LDR resistance is low, so the Arduino reads a high analog value. At
dusk the LDR resistance rises, the analog value falls, and when it
drops below the threshold the Arduino energises the relay, turning
the lamp on. A small hysteresis gap (separate on/off thresholds)
stops the light flickering at the switching point.

## Components

| Component | Value / spec | Qty |
|-----------|--------------|-----|
| Arduino Uno | — | 1 |
| LDR | e.g. GL5528 | 1 |
| Resistor | 10 kΩ (LDR divider) | 1 |
| Relay module | 5 V, 1-channel, opto-isolated | 1 |
| LED lamp / bulb | 12 V DC LED (safe option) or 230 V AC lamp via relay | 1 |
| Resistor | 220 Ω (status LED) | 1 |
| LED | 5 mm, status | 1 |
| Breadboard, jumper wires | — | — |

## Circuit diagram (text)

```
5V ── LDR ──┬── A0 (Arduino)
            │
            └── 10k resistor ── GND

Arduino D7 ── Relay IN1
Relay COM ─── Lamp ─── Power (12 V DC, or AC live via relay)
Relay NO ──── Power return / AC neutral side
             (lamp is ON only when relay is energised)

Arduino D13 ── 220Ω ── Status LED ── GND
Arduino 5V/GND ── Relay VCC / GND
```

Relay logic: the code uses an **active-LOW** relay module (LOW =
relay ON). The relay is OFF on startup.

## Wiring steps

1. Build the LDR divider: 5 V → LDR → A0 node → 10 kΩ → GND.
2. Connect the relay module: VCC → 5 V, GND → GND, IN1 → D7.
3. Connect the lamp to the relay's COM and NO terminals.
   **For a 230 V AC lamp, get a qualified electrician to wire the
   AC side. For testing, use a 12 V DC LED lamp.**
4. Connect the status LED: D13 → 220 Ω → LED anode, LED cathode → GND.
5. Upload `automatic-street-light.ino`, then open the Serial Monitor
   (9600 baud) to see the LDR reading.

## Calibration

Watch the LDR value in the Serial Monitor in daylight and in darkness.
Adjust `DUSK_THRESHOLD` (default 400) and `DAWN_THRESHOLD`
(default 500) in the code to suit your location — a higher threshold
turns the light on earlier in the evening.

## Safety notes

- Relays switch the lamp, not the Arduino. Never let mains wiring
  touch the Arduino or the breadboard.
- Relay is OFF on startup, so the lamp stays off if the Arduino
  resets.
- If using a 230 V AC lamp, keep the relay module enclosed and
  unplug it before touching any AC wiring.
