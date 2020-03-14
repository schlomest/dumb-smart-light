#include <SoftwareSerial.h>

const byte rxPin = 2;
const byte txPin = 3;
const byte keyPin = 4;
const byte powerPin = 5;
const byte ledPin = 8;

bool ledState = HIGH;

SoftwareSerial BluetoothSerial(rxPin, txPin);

void setup() {
  pinMode(keyPin, OUTPUT);
  pinMode(powerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // set to low to be discoverable
  // set to high for command mode
  digitalWrite(keyPin, LOW);

  Serial.begin(9600);
  delay(2000);
  digitalWrite(powerPin, HIGH);
  BluetoothSerial.begin(38400);

  digitalWrite(ledPin, ledState);
}

void loop() {
  // read from HC-05 and write to Arduino Serial Monitor
  if (BluetoothSerial.available()) {

    char data = BluetoothSerial.read();

    // turn on if 0 is received
    // turn off if 1 is received
    if (data == 49 && ledState == LOW) {
      Serial.println("turn on");
      ledState = HIGH;
      digitalWrite(ledPin, ledState);
    } else if (data == 48 && ledState == HIGH) {
      Serial.println("turn off");
      ledState = LOW;
      digitalWrite(ledPin, ledState);
    } else {
      Serial.println("error");
    }

    Serial.write(data);
  }

  // read Arduino Serial Monitor and write to HC-05
  if (Serial.available())
    BluetoothSerial.write(Serial.read());
}
