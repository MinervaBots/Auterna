const int op_pin = 25;

void setup() {
  // put your setup code here, to run once:
  pinMode(op_pin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalReadFast(op_pin) == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("high");
  }
    
  else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("low");    
  }
  
}
