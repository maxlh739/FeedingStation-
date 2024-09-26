#define MAGNETSWITCHPIN 47

#define MOTOR_IN1 22
#define MOTOR_IN2 23

void setup() {
  Serial.begin(9600);

  Serial.println("DRV8871 test");
  
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MAGNETSWITCHPIN, INPUT);
}

void loop() {
  // Go away from current magnet
  Serial.println("Go away from Magnet");
  int stuckCounter = 0;

  while (digitalRead(MAGNETSWITCHPIN) == 0) {
    if (stuckCounter < 6) {
      Serial.println("Softturn");
      for (int i = 128; i < 134; i++) {
        analogWrite(MOTOR_IN1, i);
        delay(4);
      }
      digitalWrite(MOTOR_IN1, LOW);
      delay(1000);

      stuckCounter++;
    } else {
      // After 6 attempts: reverse direction
      Serial.println("Stuck, reversing");
      for (int i = 128; i < 136; i++) {
        analogWrite(MOTOR_IN2, i);  // Use MOTOR_IN2 to reverse direction
        delay(4);
      }
      digitalWrite(MOTOR_IN2, LOW);
      delay(1000);

      Serial.println("Hardturn");
      for (int i = 128; i < 138; i++) {
        analogWrite(MOTOR_IN1, i);
        delay(4);
      }
      digitalWrite(MOTOR_IN1, LOW);
      delay(1000);

      stuckCounter = 0;  // Reset counter after reversing
    }
  }

  // When the magnet switch changes, stop the motor
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  Serial.println("Magnet switch changed, stopping motor");
  delay(1000);  // Optional delay before checking again

  // Go to next magnet
  Serial.println("Go to next Magnet");
  stuckCounter = 0;

  while (digitalRead(MAGNETSWITCHPIN) == 1) {
    if (stuckCounter < 6) {
      Serial.println("Softturn to next magnet");
      for (int i = 128; i < 134; i++) {
        analogWrite(MOTOR_IN1, i);
        delay(4);
      }
      digitalWrite(MOTOR_IN1, LOW);
      delay(1000);

      stuckCounter++;
    } else {
      // After 6 attempts: reverse direction
      Serial.println("Stuck, reversing to find next magnet");
      for (int i = 128; i < 136; i++) {
        analogWrite(MOTOR_IN2, i);  // Use MOTOR_IN2 to reverse direction
        delay(4);
      }
      digitalWrite(MOTOR_IN2, LOW);
      delay(1000);

      Serial.println("Hardturn to next magnet");
      for (int i = 128; i < 138; i++) {
        analogWrite(MOTOR_IN1, i);
        delay(4);
      }
      digitalWrite(MOTOR_IN1, LOW);
      delay(1000);

      stuckCounter = 0;  // Reset counter after reversing
    }
  }

  // Stop motor when the next magnet is detected
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  Serial.println("Next magnet detected, stopping motor");
  
  delay(1000);
  byte n = Serial.available(); //check if charctaer(s)has been accumulated in buffer
  while ( n == 0){
    Serial.println("Wait for input");
    delay(100);
    n = Serial.available();
  }
  serialFlush();
  Serial.println("Next round");

}

void serialFlush(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}