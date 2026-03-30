// Include necessary libraries for I2C communication and LCD control
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ===================== PIN DEFINITIONS =====================
// Input pins
const int patientButton = 2;   // Button pressed by patient to call for help
const int resetButton = 3;     // Button pressed by nurse to reset the system

// Output pins
const int buzzerPin = 8;       // Buzzer for audio alert
const int ledPin = 13;         // LED for visual alert

// ===================== LCD SETUP =====================
// Create LCD object with I2C address 0x27, 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ===================== SYSTEM STATE =====================
// Stores whether the alarm is ON or OFF
bool alarmState = false;

// ===================== SETUP FUNCTION =====================
void setup() {
  // Configure button pins as inputs with internal pull-up resistors
  // This means:
  // HIGH = not pressed, LOW = pressed
  pinMode(patientButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);

  // Configure output devices
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight(); // Turn on LCD backlight

  // Display initial system status
  lcd.setCursor(0, 0);
  lcd.print("System Normal");
}

// ===================== MAIN LOOP =====================
void loop() {

  // --------- CHECK PATIENT BUTTON ---------
  // If patient presses button (LOW because of INPUT_PULLUP)
  if (digitalRead(patientButton) == LOW) {
    alarmState = true;  // Activate alarm
  }

  // --------- CHECK RESET BUTTON ---------
  // If nurse presses reset button
  if (digitalRead(resetButton) == LOW) {
    alarmState = false; // Deactivate alarm
  }

  // --------- SYSTEM OUTPUT CONTROL ---------
  if (alarmState) {
    // ===== ALARM ACTIVE =====

    // Turn ON buzzer (sound alert)
    tone(buzzerPin, 1000);  // 1000 Hz tone

    // Turn ON LED (visual alert)
    digitalWrite(ledPin, HIGH);

    // Display alert message on LCD
    lcd.setCursor(0, 0);
    lcd.print("PATIENT ALERT! ");
    lcd.setCursor(0, 1);
    lcd.print("Need Help      ");

  } else {
    // ===== SYSTEM NORMAL =====

    // Turn OFF buzzer
    noTone(buzzerPin);

    // Turn OFF LED
    digitalWrite(ledPin, LOW);

    // Display normal status
    lcd.setCursor(0, 0);
    lcd.print("System Normal  ");
    lcd.setCursor(0, 1);
    lcd.print("               "); // Clear second line
  }
}