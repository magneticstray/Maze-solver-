



const int ledPin = D1;      // On-board LED or external LED
const int sensorPin = A0; // Or whatever pin you are using


// change this according to the room 
const float K = -526.13;
const float C = 329.46;


void setup() {
  Serial.begin(115200);
}


void loop() {
  // Read the raw analog value
  int sensorValue = analogRead(sensorPin);


  // Calculate the distance using your formula
  float distanceCm = K / (sensorValue - C);


  // IMPORTANT: Add a check for the reliable range
  if (distanceCm > 2 && distanceCm < 10) {
    Serial.print("Wall detected at: ");
    Serial.print(distanceCm);
    Serial.println(" cm");
  } else {
    Serial.println("Distance is outside of reliable range.");
  }


  delay(250);
}


