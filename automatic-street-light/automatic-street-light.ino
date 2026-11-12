/*
  Automatic Street Light
  ----------------------
  LDR senses ambient light. At dusk the relay turns the street
  light ON; at dawn it turns it OFF. Hysteresis stops flickering
  at the switching point. Relay is OFF on startup (safe default).

  Wiring:
    LDR divider: 5V - LDR - A0 - 10k resistor - GND
    Relay IN1  : D7  (active-LOW relay module)
    Status LED : D13 (through a 220 ohm resistor to GND)
*/

// ---- Pin definitions ----
const int LDR_PIN    = A0;  // LDR voltage divider
const int RELAY_PIN  = 7;   // Relay module IN1 (active LOW)
const int STATUS_LED = 13;  // Built-in / status LED

// ---- Thresholds (0-1023). Tune from Serial Monitor readings. ----
// Light ON when reading falls below DUSK_THRESHOLD,
// light OFF when reading rises above DAWN_THRESHOLD.
const int DUSK_THRESHOLD = 400;
const int DAWN_THRESHOLD = 500;

bool lightOn = false;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);

  // Safe defaults: relay OFF, lamp OFF on startup.
  digitalWrite(RELAY_PIN, HIGH);  // HIGH = relay OFF (active LOW)
  digitalWrite(STATUS_LED, LOW);

  Serial.begin(9600);
  Serial.println("Automatic Street Light ready.");
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("LDR: ");
  Serial.println(ldrValue);

  if (!lightOn && ldrValue < DUSK_THRESHOLD) {
    // It is getting dark: turn the light ON.
    lightOn = true;
    digitalWrite(RELAY_PIN, LOW);   // LOW = relay ON
    digitalWrite(STATUS_LED, HIGH);
    Serial.println("Dusk detected - street light ON");
  } else if (lightOn && ldrValue > DAWN_THRESHOLD) {
    // It is getting light: turn the light OFF.
    lightOn = false;
    digitalWrite(RELAY_PIN, HIGH);  // HIGH = relay OFF
    digitalWrite(STATUS_LED, LOW);
    Serial.println("Dawn detected - street light OFF");
  }

  delay(500);  // Check twice a second
}
