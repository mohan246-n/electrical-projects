# Home Automation Relay

Control up to 4 home loads (lights, fan, etc.) from an ESP32 or
Arduino, with a physical manual override switch for each channel,
so the lights still work even if the controller is off.

## How it works

Each of the 4 relay channels is driven by a GPIO pin. A manual
switch on each channel toggles that channel directly in software
(the switch is read each loop and toggles the relay on a press).
The relays are OFF on startup. The serial interface accepts simple
commands (`1`–`4` toggles a channel, `0` turns all off, `A` turns
all on), so a Bluetooth / Wi-Fi module can be added later without
changing the relay logic.

On ESP32 the relay pins below are used; on Arduino Uno use pins
2, 3, 4, 5 for the relays and 8, 9, 10, 11 for the switches.

## Components

| Component | Value / spec | Qty |
|-----------|--------------|-----|
| ESP32 DevKit (or Arduino Uno) | — | 1 |
| Relay module | 5 V, 4-channel, opto-isolated | 1 |
| Push buttons / toggle switches | manual override | 4 |
| Resistors | 10 kΩ pull-down for each switch | 4 |
| Loads | 12 V DC lamps / fan (safe option) or 230 V AC lights/fan | 4 |
| LEDs + 220 Ω resistors | channel status (optional) | 4 |
| Breadboard, jumper wires | — | — |

## Circuit diagram (text)

```
ESP32 GPIO 18 ── Relay IN1 ──┐
ESP32 GPIO 19 ── Relay IN2 ──┤  Relay COM/NO ── Load 1-4
ESP32 GPIO 21 ── Relay IN3 ──┤  (each load on its own channel)
ESP32 GPIO 22 ── Relay IN4 ──┘

ESP32 GPIO 32 ── Switch 1 ── 3V3      (10k pull-down to GND)
ESP32 GPIO 33 ── Switch 2 ── 3V3
ESP32 GPIO 25 ── Switch 3 ── 3V3
ESP32 GPIO 26 ── Switch 4 ── 3V3

Relay VCC ── 5V (separate 5V supply recommended for 4 relays)
Relay GND ── GND (common with ESP32)
```

Relay logic: active-LOW modules — LOW = relay ON, HIGH = relay OFF.

## Wiring steps

1. Connect relay IN1–IN4 to the GPIO pins above; VCC to 5 V, GND to GND.
2. Connect each load between the relay COM and NO terminals.
   **For 230 V AC loads, get a qualified electrician to wire the
   AC side. Test first with 12 V DC lamps.**
3. Connect each manual switch between 3V3 and its GPIO pin, with a
   10 kΩ resistor from the GPIO pin to GND.
4. Upload `home-automation-relay.ino` (select ESP32 DevKit, or
   Arduino Uno with the pin notes above).
5. Press a switch to toggle its channel; or send `1`–`4` over
   Serial (9600 baud) to toggle, `A` for all on, `0` for all off.

## Safety notes

- All 4 relays OFF on startup — no load turns on unexpectedly.
- Use a separate 5 V supply for the relay board if the ESP32
  resets when relays switch (relay coils draw significant current).
- Keep mains wiring enclosed and separate from the low-voltage side.
  Unplug before touching AC wiring.
- Do not exceed the relay module's rated current per channel
  (typically 10 A at 250 V AC).
