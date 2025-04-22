/// TRIAL ON WOKWI.COM
/// PROJECT LINK: 	https://wokwi.com/projects/428542154413764609
int ledGate = 2; /// FADE RED
int ledGate2 = 7; /// FADE BLUE
int analogPin = A0; /// MQ-2
int analogPin1 = A1; /// LDR
int smokeThreshold = 400; /// even clean air, always >= 200
int lightThreshold = 400; /// light value
int relayGate = 8; /// pink
int buzzerGate = 11; /// brown, passive
void setup() {
  // put your setup code here, to run once:
  pinMode(ledGate, OUTPUT);
  pinMode(ledGate2, OUTPUT);
  pinMode(relayGate, OUTPUT);
  pinMode(buzzerGate, OUTPUT);
  /// relay low -> open
  /// relay high -> disconnect
}

void loop() {
  // put your main code here, to run repeatedly:
  /// SENSORS AREA
  int mq2analogValue = analogRead(analogPin);
  int ldranalogValue = analogRead(analogPin1);
  if (mq2analogValue > smokeThreshold) {
    digitalWrite(ledGate,HIGH);
  }
  else if (mq2analogValue <= smokeThreshold) {
    digitalWrite(ledGate,LOW);
    digitalWrite(relayGate, HIGH);
  }
  if (ldranalogValue <= lightThreshold) {
    digitalWrite(ledGate2,HIGH);
    digitalWrite(relayGate, HIGH);
  }
  else if (ldranalogValue > lightThreshold) {
    digitalWrite(ledGate2,LOW);
    digitalWrite(relayGate, LOW);
  }
  /// BUZZER AREA
  if (mq2analogValue > smokeThreshold || ldranalogValue <= lightThreshold) {
    tone(buzzerGate, 1000);
  }
  else {
    noTone(buzzerGate);
  }
}
