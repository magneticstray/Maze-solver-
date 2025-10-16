#define TRIG_PIN 5
#define ECHO_PIN 6

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("Ultrasonic Test Started");
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // add timeout to avoid watchdog reset
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout = 30ms

  if (duration == 0) {
    Serial.println("No echo detected!");
  } else {
    float distance = (duration * 0.0343) / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(500);
}
