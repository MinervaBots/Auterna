void setup() {
  // put your setup code here, to run once:
  pinMode(A21, OUTPUT);
  pinMode(A22, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  analogWriteResolution(12);

  Serial.begin(9600);
  Serial.println("---- BOOT ----");
}

uint8_t sig = 0;
void loop() {
  Serial.println("Loop");
  // analogWrite(A21, sig);
  // analogWrite(A22, sig++);
  // sig %= 256;
  // delay(50);

  analogWrite(A21,4095);
  // Teensy tem uma referência interna para o DAC
  // de 3.3V. Para alcançar 2.0V, usar 2481 como
  // máximo
  analogWrite(A22,4095);
}
