const int sensorPin = A0;
const int irled = D1;


float distances[] = {3, 5, 7, 10, 15, 20};
int numPoints = sizeof(distances) / sizeof(distances[0]);


int readings[10];


int ambientOffset = 0;




void setup() {
  Serial.begin(115200);
  delay(2000);


  Serial.println("\n--- STAGE 1: Ambient Light Calibration ---");
  Serial.println("To begin, please COMPLETELY COVER the IR Emitter LED (the clear one).");
  Serial.println("Do NOT cover the black receiver sensor.");
  Serial.println("Then, type 'c' and press Enter to calibrate.");


  while (Serial.read() != 'c') {
  }
 
  while (Serial.available() > 0) Serial.read();


  long sum = 0;
  for (int i = 0; i < 15; i++) {
    sum += analogRead(sensorPin);
    delay(20);
  }
  ambientOffset = sum / 15;


  Serial.print("\nCalibration complete! Ambient light offset is: ");
  Serial.println(ambientOffset);
  Serial.println("You can now UNCOVER the LED.");
  Serial.println("----------------------------------------\n");
  delay(3000);


  Serial.println("--- STAGE 2: Distance Calibration ---");
  Serial.println("Place a white object at each distance when prompted.\n");


  for (int i = 0; i < numPoints; i++) {
    Serial.print("Place object at ");
    Serial.print(distances[i]);
    Serial.println(" cm and press ENTER...");


    while (Serial.available() == 0);
    while (Serial.available() > 0) Serial.read();


    long readingSum = 0;
    for (int j = 0; j < 10; j++) {
      int correctedReading = analogRead(sensorPin) - ambientOffset;
      readingSum += correctedReading;
      delay(100);
    }
   
    int finalReading = readingSum / 10;


    if (finalReading < 0) {
      finalReading = 0;
    }
   
    readings[i] = finalReading;


    Serial.print("Corrected Value: ");
    Serial.println(readings[i]);
    Serial.println("--------------------");
  }


  Serial.println("\n--- Raw Corrected Data ---");
  Serial.println("Distance(cm)\tSensorValue");
  for (int i = 0; i < numPoints; i++) {
    Serial.print(distances[i]);
    Serial.print("\t\t");
    Serial.println(readings[i]);
  }


  float sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
  for (int i = 0; i < numPoints; i++) {
    float x = readings[i];
    float y = 1.0 / distances[i];
    sumX += x;
    sumY += y;
    sumXY += x * y;
    sumX2 += x * x;
  }


  float denom = (numPoints * sumX2 - sumX * sumX);
  float a = (numPoints * sumXY - sumX * sumY) / denom;
  float b = (sumY * sumX2 - sumX * sumXY) / denom;


  float K = 1.0 / a;
  float C = -b * K;


  Serial.println("\n--- Curve Fit Results ---");
  Serial.println("Your new calibration constants are:");
  Serial.print("K = "); Serial.println(K, 2);
  Serial.print("C = "); Serial.println(C, 2);
  Serial.print("\nBest-fit equation: distance = ");
  Serial.print(K, 2);
  Serial.print(" / (sensorValue - ");
  Serial.print(C, 2);
  Serial.println(")");
  Serial.println("\nYou can now plug these new K and C values into your main robot code.");


  Serial.println("\n--- Predicted vs Actual ---");
  for (int i = 0; i < numPoints; i++) {
    float predicted = K / (readings[i] - C);
    Serial.print("Actual: ");
    Serial.print(distances[i]);
    Serial.print(" cm | Predicted: ");
    Serial.print(predicted, 2);
    Serial.println(" cm");
  }


  Serial.println("\n--- Calibration Finished ---");
}


void loop() {
}
