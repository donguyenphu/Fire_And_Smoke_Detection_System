/// real code I used on my product
/// I put the LED for testing
int ledGate = 2; /// FADE RED
int ledGate2 = 7; /// FADE BLUE
int analogPin = A0; /// MQ-2
int analogPin1 = A1; /// LDR
int smokeThreshold = 400; /// even clean air, always >= 200
int lightThreshold = 600; /// light value
int relayGate = 8; /// pink
int buzzerGate = 11; /// brown, passive

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledGate, OUTPUT);
  pinMode(ledGate2, OUTPUT);
  pinMode(relayGate, OUTPUT);
  pinMode(buzzerGate, OUTPUT);
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
  if (mq2analogValue > smokeThreshold || ldranalogValue <= lightThreshold) {
    digitalWrite(relayGate, LOW);
    tone(buzzerGate, 1000);
  }
  else {
    noTone(buzzerGate);
    digitalWrite(relayGate, HIGH);
  }
}
