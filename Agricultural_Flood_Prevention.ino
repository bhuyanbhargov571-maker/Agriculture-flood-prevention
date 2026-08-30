#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ── Pin Definitions ──────────────────────────────────────
#define DIGITAL_SENSOR_PIN  2      // Nodemcu input (HIGH = Available)
#define ANALOG_SENSOR_PIN   A0     // water level sensor input
#define TRIG_PIN            9      // Ultrasonic TRIG
#define ECHO_PIN            10     // Ultrasonic ECHO
#define RELAY_PIN           7      // Relay output (active Low)

// ── Settings ─────────────────────────────────────────────
#define DISTANCE_LIMIT_CM   20     // ← Set your distance threshold here
#define LCD_I2C_ADDR        0x27   // Common I2C address (try 0x3F if blank)
#define LCD_COLS            16
#define LCD_ROWS            2

// ── LCD Object ───────────────────────────────────────────
LiquidCrystal_I2C lcd(LCD_I2C_ADDR, LCD_COLS, LCD_ROWS);

// ── Timing ───────────────────────────────────────────────
unsigned long lastUpdate = 0;
const unsigned long UPDATE_INTERVAL = 200; // ms between sensor reads

// ─────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);

  pinMode(DIGITAL_SENSOR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH); // Relay OFF (active LOW module)

  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Startup splash
  lcd.setCursor(0, 0);
  lcd.print("  System Ready  ");
  lcd.setCursor(0, 1);
  lcd.print("  Initializing..");
  delay(1500);
  lcd.clear();
}

// ─────────────────────────────────────────────────────────
float readUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout (~5m max)
  if (duration == 0) return -1.0; // Out of range / no echo

  return (duration * 0.0343) / 2.0; // Convert to cm
}

// ─────────────────────────────────────────────────────────
void loop() {
  unsigned long now = millis();
  if (now - lastUpdate < UPDATE_INTERVAL) return;
  lastUpdate = now;

  // ── 1. Read all sensors ────────────────────────────────
  bool  isAvailable  = digitalRead(DIGITAL_SENSOR_PIN) == HIGH;
  int   analogRaw    = analogRead(ANALOG_SENSOR_PIN);
  float distanceCM   = readUltrasonic();

  // ── 2. LCD Line 1 — Digital status ────────────────────
  lcd.setCursor(0, 0);
  if (isAvailable) {
    lcd.print("Rain Alert");
  } else {
    lcd.print("No Alert");  // 16 chars fits exactly
  }

// ── 3. LCD Line 2 — Analog as percentage ──────────────
  int analogPercent = map(analogRaw, 0, 1023, 0, 100);

  lcd.setCursor(0, 1);
  lcd.print("Rain Level: ");
  lcd.print(analogPercent);
  lcd.print("%   "); // Blank-pad to clear leftover digits

  // ── 4. Relay Logic ─────────────────────────────────────
  //    Activate ONLY when:
  //      a) Digital sensor reports "Available"
  //      b) Ultrasonic distance < DISTANCE_LIMIT_CM
  bool distanceTriggered = (distanceCM > 0) && (distanceCM < DISTANCE_LIMIT_CM);
  bool relayActive       = isAvailable && distanceTriggered;

  digitalWrite(RELAY_PIN, relayActive ? LOW : HIGH); // Active LOW

  // ── 5. Serial debug ────────────────────────────────────
  Serial.print("Digital: ");
  Serial.print(isAvailable ? "Available" : "Not Active");
  Serial.print(" | Analog: ");
  Serial.print(analogRaw);
  Serial.print(" | Distance: ");
  if (distanceCM < 0) Serial.print("OOR");
  else { Serial.print(distanceCM, 1); Serial.print(" cm"); }
  Serial.print(" | Relay: ");
  Serial.println(relayActive ? "ON" : "OFF");
}
