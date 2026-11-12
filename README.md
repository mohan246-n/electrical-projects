# Electrical Projects

A collection of 5 practical, beginner-friendly Arduino-based electrical
projects, built for learning, home use, and portfolio / college work.
Each project lives in its own folder with its own README, working
Arduino code (`.ino`), and a text circuit diagram.

## Projects

| # | Project | What it does |
|---|---------|--------------|
| 1 | [automatic-street-light](automatic-street-light/) | Street light turns on automatically at dusk and off at dawn, using an LDR sensor and a relay. |
| 2 | [home-automation-relay](home-automation-relay/) | 4-channel relay board controls lights and a fan, with a manual override switch for each channel. |
| 3 | [solar-battery-charger-monitor](solar-battery-charger-monitor/) | Monitors a solar panel and a 12 V battery, shows voltage on LCD/serial, and cuts off charging when the battery is full. |
| 4 | [digital-voltmeter](digital-voltmeter/) | Measures 0–25 V DC with a voltage divider and shows the reading on a 16×2 LCD. |
| 5 | [smoke-fire-alarm](smoke-fire-alarm/) | MQ-2 smoke sensor triggers a buzzer and LED alarm when smoke crosses a threshold. |

## How to use

1. Pick a project folder and read its `README.md` first — it lists the
   exact components, wiring, and safety notes for that project.
2. Open the `.ino` file in the Arduino IDE (or Arduino CLI / VS Code
   with the Arduino extension).
3. Select your board (Arduino Uno unless the project says ESP32) and
   the correct port, then upload.
4. Wire the circuit exactly as described in the project README.
   **Do not power the circuit until you have double-checked the wiring.**
5. Open the Serial Monitor at 9600 baud (where the project uses it)
   to see readings and status messages.

## Common components and tools

- Arduino Uno (projects 1, 3, 4, 5) / ESP32 DevKit (project 2)
- Breadboard, jumper wires, USB cable
- Resistors: 10 kΩ, 1 kΩ, 220 Ω (see each project for exact values)
- 5 V relay module(s), LEDs, buzzer, push buttons / switches
- LDR, MQ-2 gas sensor, 16×2 LCD (with I2C backpack where noted)
- Solar panel (12 V, 10–20 W) and 12 V lead-acid battery (project 3)
- Multimeter, wire stripper, screwdriver, soldering iron (optional)

## ⚠️ Safety warnings — read before building anything

- **Mains voltage (230 V AC in India / 110–240 V AC elsewhere) can kill.**
  Projects in this repo switch mains loads only through an enclosed
  relay module, and the low-voltage Arduino side must be kept fully
  separate from the mains side. If you are not confident working with
  mains wiring, get a qualified electrician to wire the AC side, or
  build the project with a low-voltage DC load (e.g. a 12 V lamp)
  instead.
- Never touch the relay module's screw terminals or mains wires while
  the circuit is powered. Always unplug / switch off at the wall
  before changing wiring.
- Check every connection with a multimeter before first power-up.
  Reversed polarity on the battery / solar project can damage the
  Arduino and the battery.
- The voltage-divider projects (3 and 4) are for **DC only**.
  Never connect them to AC mains.
- The MQ-2 sensor gets warm in normal use — that is expected.
  It detects smoke/gas; it is a warning device, not a substitute for
  a certified fire alarm system or for calling emergency services.
- Keep batteries away from heat and short circuits. Use a fuse
  (e.g. 5 A) in series with a 12 V battery where the project says so.

## Repo layout

```
electrical-projects/
├── README.md
├── LICENSE
├── .gitignore
├── automatic-street-light/
├── home-automation-relay/
├── solar-battery-charger-monitor/
├── digital-voltmeter/
└── smoke-fire-alarm/
```

## Pushing to GitHub

```bash
git init
git add .
git commit -m "Add 5 Arduino electrical projects"
git branch -M main
git remote add origin https://github.com/<your-username>/electrical-projects.git
git push -u origin main
```

## License

MIT — see [LICENSE](LICENSE).
