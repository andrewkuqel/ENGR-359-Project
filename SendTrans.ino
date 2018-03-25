#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN

const int pinfive = 5;
const int pinsix = 6;

const byte address[][6] = {"00001","00002"};
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(pinsix,OUTPUT);
  digitalWrite(pinsix,HIGH);
   pinMode(pinfive,OUTPUT);
  digitalWrite(pinfive,HIGH);
  
}
void loop() {
 delay(5);

 

 int sensorValuea = analogRead(A0); //Need to optimize the resistance value
 int angleValuea = map(sensorValuea,446,464,0,180);
 
 


 int sensorValueb = analogRead(A1); //Need to optimize the resistance value
 int angleValueb = map(sensorValueb,485,520,0,180);


 Serial.println(sensorValueb);
if((446 <= angleValuea <= 464) && (485 <= angleValueb <= 520)) {
  radio.openWritingPipe(address[0]);
  radio.write(&angleValuea,sizeof(angleValuea));
  
  radio.openWritingPipe(address[1]);
  radio.write(&angleValueb,sizeof(angleValueb));
 }
  else if ( 446 <= angleValuea <= 464) {
 radio.openWritingPipe(address[0]);
 radio.write(&angleValuea,sizeof(angleValuea));
 
  
 }
 else if ( 485 <= angleValueb <= 520) {
  radio.openWritingPipe(address[1]);
 radio.write(&angleValueb,sizeof(angleValueb));
 }

 }
 



