#include <Wire.h>
#include <Adafruit_PN532.h>

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

uint8_t SELECT_APDU[] = {
  0x00, /* CLA */
  0xA4, /* INS */
  0x04, /* P1  */
  0x00, /* P2  */
  0x05, /* Length of AID  */
  0xF2, 0x22, 0x22, 0x22, 0x22 /* AID  */
};

void setup(void) {
  Serial.begin(115200);
  Serial.println("Hello!");

  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1);
  }

  nfc.SAMConfig();
  Serial.println("Waiting for an NFC card...");
}

void loop(void) {
  if(true){
    ReadHostCardEmulation();
  }else{
    ReadCard();
  }
}

void ReadHostCardEmulation(){
  //Serial.println("Listening...");
  if (nfc.inListPassiveTarget()) {
    Serial.println("Something's there...");

    uint8_t response[255];
    uint8_t responseLength = sizeof(response);

    bool success = nfc.inDataExchange(SELECT_APDU, sizeof(SELECT_APDU), response, &responseLength);

    if (success) {
      Serial.println("Sent");
      nfc.PrintHexChar(response, responseLength);
    } else {
      Serial.println("Not sent");
    }
  }
  delay(1000);
}

void ReadCard(){
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    Serial.println("Found an NFC card!");

    Serial.print("UID Length: ");
    Serial.print(uidLength, DEC);
    Serial.println(" bytes");
    Serial.print("UID Value: ");
    for (uint8_t i=0; i < uidLength; i++) {
      Serial.print(" 0x");
      Serial.print(uid[i], HEX);
    }
    Serial.println("");

    delay(1000);
  }
}