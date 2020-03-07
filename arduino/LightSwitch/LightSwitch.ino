#include <SoftwareSerial.h>

const byte rxPin = 2;
const byte txPin = 3;
const byte keyPin = 4;
const byte powerPin = 5;
const byte ledPin = 8;

bool ledState = true;

SoftwareSerial BluetoothSerial(rxPin, txPin);

void setup() {
  pinMode(keyPin, OUTPUT);
  pinMode(powerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(keyPin, HIGH);

  Serial.begin(9600);
  delay(2000);
  Serial.println("hello there");
  digitalWrite(powerPin, HIGH);
  BluetoothSerial.begin(38400);

  digitalWrite(ledPin, HIGH);
}

void loop() {
  //  digitalWrite(ledPin, HIGH);
  //  delay(1000);
  //  digitalWrite(ledPin, LOW);
  //  delay(1000);

  // read from HC-05 and write to Arduino Serial Monitor
  if (BluetoothSerial.available()) {
    Serial.println(BluetoothSerial.available());
    Serial.println("message received");

    char data = BluetoothSerial.read();

    // check if char is "O" from the "OK" message
    if (data == 79) {
      if (ledState) {
        Serial.println("turn off");
        digitalWrite(ledPin, LOW);
      } else {
        Serial.println("turn on");
        digitalWrite(ledPin, HIGH);
      }
      ledState = !ledState;
    }

    Serial.write(data);
  }

  // read Arduino Serial Monitor and write to HC-05
  if (Serial.available())
    BluetoothSerial.write(Serial.read());
}