#include "src/Button/Button.h"

constexpr int button =  11;

Button b {button};

void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  // b.setState(digitalRead(button));
  Serial.begin(9600);
}

bool isOn = false;
void loop() {
  // put your main code here, to run repeatedly:
  if(b.toggled())
    isOn = !isOn;
  
//  if(isOn)
//    Serial.println("ON");
//  else
//    Serial.println("OFF");

  Serial.println(b.read());
}
