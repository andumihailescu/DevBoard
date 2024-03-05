#include <ESP32Servo.h>

int ledPin = 2;
Servo myServo;
//A12, GND A19 & 3v3 J19
int servoPin = 19;

void setup() {
  pinMode(ledPin, OUTPUT);
  myServo.attach(servoPin);
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()){
    int angle = Serial.parseInt();
    myServo.write(angle);
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
  }
  delay(20);
}
