#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  servo1.attach(9); //finger 1 need pwm pins
  servo2.attach(6); //finger 2
  servo3.attach(5); //finger 3
  servo4.attach(3); //finger 4
  
}
void loop() {
  while (radio.available()) {
    int angleServ;
    radio.read(&angleServ,sizeof(angleServ));
    servo1.write(angleServ);
    servo2.write(angleServ);
    servo3.write(angleServ);
    servo4.write(angleServ);
    Serial.println(angleServ);
  }
}
