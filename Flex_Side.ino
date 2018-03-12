#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
const int flex_thumb = A0
const int flex_finger = A1
int data[2]

void setup(){
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
}

void loop(){
  value_thumb = analogRead(flex_thumb);
  value_finger = analogRead(flex_finger);
  Serial.println(value_thumb);
  Serial.println(value_finger);
  data[0] = map(value_finger, 700, 900, 0, 255);
  data[1] = map(value_thumb, 700, 900, 0, 255);
  radio.write(&data, sizeof(text));
  delay(1000);
}
