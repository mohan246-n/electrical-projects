/*
  Home Automation Relay — 4 channels
  -----------------------------------
  4-channel relay board controls lights / fan, with a manual
  override switch per channel. Relays are OFF on startup
  (safe default). Serial commands: '1'-'4' toggle a channel,
  'A' = all on, '0' = all off.

  Default pins are for ESP32 DevKit. For Arduino Uno use:
    relays  = {2, 3, 4, 5}
    switches = {8, 9, 10, 11}
  Relay modules are active-LOW: LOW = relay ON.
*/

// ---- Pin definitions (ESP32) ----
const int RELAY_PINS[4]  = {18, 19, 21, 22};
const int SWITCH_PINS[4] = {32, 33, 25, 26};

bool channelOn[4]      = {false, false, false, false};
bool lastSwitchState[4] = {LOW, LOW, LOW, LOW};

void setChannel(int ch, bool on) {
  channelOn[ch] = on;
  // Active-LOW relay: LOW turns the relay ON.
  digitalWrite(RELAY_PINS[ch], on ? LOW : HIGH);
  Serial.print("Channel ");
  Serial.print(ch + 1);
  Serial.println(on ? " ON" : " OFF");
}

void toggleChannel(int ch) {
  setChannel(ch, !channelOn[ch]);
}

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 4; i++) {
    pinMode(RELAY_PINS[i], OUTPUT);
    pinMode(SWITCH_PINS[i], INPUT);
    // Safe default: all relays OFF on startup.
    digitalWrite(RELAY_PINS[i], HIGH);
  }

  Serial.println("Home Automation Relay ready.");
  Serial.println("Send 1-4 to toggle a channel, A = all on, 0 = all off.");
}

void loop() {
  // Manual override switches (with simple debounce).
  for (int i = 0; i < 4; i++) {
    bool state = digitalRead(SWITCH_PINS[i]);
    if (state == HIGH && lastSwitchState[i] == LOW) {
      delay(50);  // Debounce
      if (digitalRead(SWITCH_PINS[i]) == HIGH) {
        toggleChannel(i);
      }
    }
    lastSwitchState[i] = state;
  }

  // Serial commands.
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd >= '1' && cmd <= '4') {
      toggleChannel(cmd - '1');
    } else if (cmd == 'A' || cmd == 'a') {
      for (int i = 0; i < 4; i++) setChannel(i, true);
    } else if (cmd == '0') {
      for (int i = 0; i < 4; i++) setChannel(i, false);
    }
  }

  delay(10);
}
