

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int patientButton = 2;
const int resetButton = 3;
const int buzzerPin = 8;
const int ledPin = 13;

LiquidCrystal_I2C lcd(0x27, 16, 2);

bool alarmState = false;

void setup() {
  pinMode(patientButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("System Normal");
}

void loop() {
  if (digitalRead(patientButton) == LOW) {
    alarmState = true;
  }

  if (digitalRead(resetButton) == LOW) {
    alarmState = false;
  }

  if (alarmState) {
    tone(buzzerPin, 1000);
    digitalWrite(ledPin, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("PATIENT ALERT! ");
    lcd.setCursor(0, 1);
    lcd.print("Need Help      ");
  } else {
    noTone(buzzerPin);
    digitalWrite(ledPin, LOW);

    lcd.setCursor(0, 0);
    lcd.print("System Normal  ");
    lcd.setCursor(0, 1);
    lcd.print("               ");
  }
}