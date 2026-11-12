/*
  Smoke / Fire Alarm
  ------------------
  MQ-2 sensor watches for smoke. Above the threshold the buzzer
  sounds and the alarm LED flashes until the air clears.
  Buzzer and LED are OFF on startup (safe default).
  Note: the MQ-2 needs 1-2 minutes to warm up after power-on.
  This is a warning device, not a certified fire alarm.

  Wiring:
    MQ-2 A0 : A0
    MQ-2 VCC: 5V, MQ-2 GND: GND
    Buzzer  : D8 (active buzzer, + to D8, - to GND)
    Alarm LED: D13 (through a 220 ohm resistor to GND)
*/

// ---- Pin definitions ----
const int MQ2_PIN   = A0;  // MQ-2 analog output
const int BUZZER_PIN = 8;  // Buzzer
const int ALARM_LED  = 13; // Alarm LED

// ---- Thresholds (0-1023). Tune from clean-air baseline. ----
// Alarm ON above ALARM_THRESHOLD, OFF below CLEAR_THRESHOLD.
const int ALARM_THRESHOLD = 400;
const int CLEAR_THRESHOLD = 350;

bool alarmOn = false;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ALARM_LED, OUTPUT);

  // Safe defaults: buzzer and LED OFF on startup.
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(ALARM_LED, LOW);

  Serial.begin(9600);
  Serial.println("Smoke alarm warming up - please wait 1-2 minutes...");
}

void loop() {
  int smokeLevel = analogRead(MQ2_PIN);
  Serial.print("Smoke level: ");
  Serial.println(smokeLevel);

  if (!alarmOn && smokeLevel > ALARM_THRESHOLD) {
    alarmOn = true;
    Serial.println("WARNING: Smoke detected!");
  } else if (alarmOn && smokeLevel < CLEAR_THRESHOLD) {
    alarmOn = false;
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(ALARM_LED, LOW);
    Serial.println("Air clear - alarm off.");
  }

  if (alarmOn) {
    // Sound the buzzer and flash the LED.
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(ALARM_LED, HIGH);
    delay(300);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(ALARM_LED, LOW);
    delay(300);
  } else {
    delay(500);
  }
}
