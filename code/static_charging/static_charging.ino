/*************************************************
 * Static Wireless EV Charging System
 * ---------------------------------
 * Features:
 *  - IR-based vehicle detection
 *  - Relay-based power control
 *  - Charging time calculation
 *  - Billing based on charging duration
 *  - LCD display output
 *************************************************/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD configuration (I2C address 0x27, 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* ----------- Pin Definitions ----------- */
int irSensorPin1 = 2;
int irSensorPin2 = 3;
int irSensorPin3 = 4;
int irSensorPin4 = 5;

int relayPin1 = 6;
int relayPin2 = 7;
int relayPin3 = 8;
int relayPin4 = 9;

/* ----------- Time Variables ----------- */
unsigned long activationTime1 = 0, deactivationTime1 = 0, onTime1 = 0;
unsigned long activationTime2 = 0, deactivationTime2 = 0, onTime2 = 0;
unsigned long activationTime3 = 0, deactivationTime3 = 0, onTime3 = 0;
unsigned long activationTime4 = 0, deactivationTime4 = 0, onTime4 = 0;

/* ----------- Control Flags ----------- */
int x = 0, y = 0, z = 0, a = 0;
float amount = 0;

/* ----------- Setup Function ----------- */
void setup() {
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);
  pinMode(irSensorPin3, INPUT);
  pinMode(irSensorPin4, INPUT);

  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);

  // Relays OFF initially (active LOW)
  digitalWrite(relayPin1, HIGH);
  digitalWrite(relayPin2, HIGH);
  digitalWrite(relayPin3, HIGH);
  digitalWrite(relayPin4, HIGH);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

/* ----------- Loop Function ----------- */
void loop() {

  lcd.clear();

  int sensorState1 = digitalRead(irSensorPin1);
  int sensorState2 = digitalRead(irSensorPin2);
  int sensorState3 = digitalRead(irSensorPin3);
  int sensorState4 = digitalRead(irSensorPin4);

  /* ----------- Station 1 ----------- */
  if (sensorState1 == HIGH) {
    deactivationTime1 = millis();
    digitalWrite(relayPin1, HIGH);
  } else {
    activationTime1 = millis();
    digitalWrite(relayPin1, LOW);
    onTime1 = activationTime1 - deactivationTime1;
    x = 1;
  }

  if (sensorState1 == HIGH && x == 1) {
    displayBilling(1, onTime1);
    x = 0;
  }

  /* ----------- Station 2 ----------- */
  if (sensorState2 == HIGH) {
    deactivationTime2 = millis();
    digitalWrite(relayPin2, HIGH);
  } else {
    activationTime2 = millis();
    digitalWrite(relayPin2, LOW);
    onTime2 = activationTime2 - deactivationTime2;
    y = 1;
  }

  if (sensorState2 == HIGH && y == 1) {
    displayBilling(2, onTime2);
    y = 0;
  }

  /* ----------- Station 3 ----------- */
  if (sensorState3 == HIGH) {
    deactivationTime3 = millis();
    digitalWrite(relayPin3, HIGH);
  } else {
    activationTime3 = millis();
    digitalWrite(relayPin3, LOW);
    onTime3 = activationTime3 - deactivationTime3;
    z = 1;
  }

  if (sensorState3 == HIGH && z == 1) {
    displayBilling(3, onTime3);
    z = 0;
  }

  /* ----------- Station 4 ----------- */
  if (sensorState4 == HIGH) {
    deactivationTime4 = millis();
    digitalWrite(relayPin4, HIGH);
  } else {
    activationTime4 = millis();
    digitalWrite(relayPin4, LOW);
    onTime4 = activationTime4 - deactivationTime4;
    a = 1;
  }

  if (sensorState4 == HIGH && a == 1) {
    displayBilling(4, onTime4);
    a = 0;
  }

  delay(100);
}

/* ----------- Billing Display Function ----------- */
void displayBilling(int station, unsigned long onTime) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Station-");
  lcd.print(station);
  lcd.print(" ON");

  lcd.setCursor(0, 1);
  lcd.print(onTime / 1000.0);
  lcd.print(" sec");

  delay(5000);

  amount = onTime * 0.0002;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Amount:");
  lcd.setCursor(0, 1);
  lcd.print(amount);
  lcd.print(" Rs");

  delay(5000);
  amount = 0;
}
