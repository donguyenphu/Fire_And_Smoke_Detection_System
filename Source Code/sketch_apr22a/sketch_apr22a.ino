/// real code I used on my product
/// I put the LED for testing, replacing the mini dc submersible water that doesn't exist in Wokwi.com
int ledGate = 2; /// FADE RED
int ledGate2 = 7; /// FADE BLUE
int analogPin = A0; /// MQ-2
int analogPin1 = A1; /// LDR
int smokeThreshold = 400; /// even clean air, always >= 200
int lightThreshold = 700; /// light value
int relayGate = 8; /// pink
int buzzerGate = 11; /// brown, passive

/// just some fun:>
void playTone(int frequency, int duration) {
  tone(buzzerGate, frequency);
  delay(duration);  
  noTone(buzzerGate);
  delay(50); // short pause between notes
}

void playMelody() {
  playTone(262, 400); // C
  playTone(262, 400); // C
  playTone(392, 400); // G
  playTone(392, 400); // G
  playTone(440, 400); // A
  playTone(440, 400); // A
  playTone(392, 800); // G

  playTone(349, 400); // F
  playTone(349, 400); // F
  playTone(330, 400); // E
  playTone(330, 400); // E
  playTone(294, 400); // D
  playTone(294, 400); // D
  playTone(262, 800); // C
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledGate, OUTPUT);
  pinMode(ledGate2, OUTPUT);
  pinMode(relayGate, OUTPUT);
  pinMode(buzzerGate, OUTPUT);
  noTone(buzzerGate);
}

void loop() {
  // put your main code here, to run repeatedly:
  /// SENSORS AREA
  int mq2analogValue = analogRead(analogPin);
  int ldranalogValue = analogRead(analogPin1);
  Serial.println(ldranalogValue);
  /// SMOKE
  if (mq2analogValue > smokeThreshold) {
    digitalWrite(ledGate,HIGH);
    digitalWrite(relayGate, LOW); 
  }
  else if (mq2analogValue <= smokeThreshold) {
    digitalWrite(ledGate,LOW);
    digitalWrite(relayGate, HIGH);
  }
  /// LIGHT
  if (ldranalogValue <= lightThreshold) {
    digitalWrite(ledGate2,HIGH);
    digitalWrite(relayGate, LOW);
  }
  else if (ldranalogValue > lightThreshold) {
    digitalWrite(ledGate2,LOW);
    digitalWrite(relayGate, HIGH);
  }
  /// BUZZER AREA
  if (ldranalogValue <= lightThreshold || mq2analogValue > smokeThreshold) {
    digitalWrite(relayGate, LOW);
    tone(buzzerGate, 1000);
  }
  else {
    noTone(buzzerGate);
    digitalWrite(relayGate, HIGH);
  }
}
