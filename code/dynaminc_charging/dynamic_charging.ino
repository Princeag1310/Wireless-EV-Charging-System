/*************************************************
 * Dynamic Wireless EV Charging System
 * ----------------------------------
 * Features:
 *  - IR sensors detect vehicle movement
 *  - Sequential relay activation
 *  - Simulates dynamic charging lanes
 *************************************************/

int irSensorPin1 = 2;
int irSensorPin2 = 3;
int irSensorPin3 = 4;
int irSensorPin4 = 5;

int relayPin1 = 6;
int relayPin2 = 7;
int relayPin3 = 8;
int relayPin4 = 9;

void setup() {
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);
  pinMode(irSensorPin3, INPUT);
  pinMode(irSensorPin4, INPUT);

  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);

  // Turn OFF all relays initially
  digitalWrite(relayPin1, HIGH);
  digitalWrite(relayPin2, HIGH);
  digitalWrite(relayPin3, HIGH);
  digitalWrite(relayPin4, HIGH);
}

void loop() {

  int sensorState1 = digitalRead(irSensorPin1);
  int sensorState2 = digitalRead(irSensorPin2);
  int sensorState3 = digitalRead(irSensorPin3);
  int sensorState4 = digitalRead(irSensorPin4);

  // Dynamic charging logic
  digitalWrite(relayPin1, sensorState1 == LOW ? LOW : HIGH);
  digitalWrite(relayPin2, sensorState2 == LOW ? LOW : HIGH);
  digitalWrite(relayPin3, sensorState3 == LOW ? LOW : HIGH);
  digitalWrite(relayPin4, sensorState4 == LOW ? LOW : HIGH);

  delay(100);
}
