void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  Serial.println(LED_BUILTIN);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}
