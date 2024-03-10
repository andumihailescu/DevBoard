#include "BluetoothSerial.h"

BluetoothSerial serialBT;
char cmd;
int ledPin = 2;

void setup() {
  serialBT.begin("ESP32-BT");
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if(serialBT.available()){
    cmd = serialBT.read();
  }
  if(cmd == '1'){
    digitalWrite(ledPin, HIGH);
  }
  if(cmd == '0'){
    digitalWrite(ledPin, LOW);
  }
  delay(20);
}
