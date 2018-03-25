#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00002";
Servo servo5;


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  servo5.attach(10); 
 
  
}
void loop() {
  while (radio.available()) {
    int angleServ;
    radio.read(&angleServ,sizeof(angleServ));
    servo5.write(angleServ);
    Serial.println(angleServ);
  }
}
