#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

const int pinfive = 5;
const int pinsix = 6;
int angleValuea;
int angleValueb;

RF24 transmit (7,8);
const byte address [5] = {"00001"};

struct package
  {
    float thumb = 0;
    float finger = 0;
  };

typedef struct package Package;
Package data;

void setup() {
  transmit.begin();
  transmit.openWritingPipe(address);            //open writing pipe to address 00001
  transmit.setPALevel(RF24_PA_MAX);             //set RF power output to maximum
  transmit.setDataRate(RF24_250KBPS);           //set datarate to 250kbps
  transmit.setChannel(100);                     //set frequency to channel 100
  transmit.stopListening();
   pinMode(pinsix,OUTPUT);
  digitalWrite(pinsix,HIGH);
   pinMode(pinfive,OUTPUT);
  digitalWrite(pinfive,HIGH);
  }

void loop() {
 angleValuea = analogRead(A0);
   data.thumb= map(angleValuea,446,464,0,180);
 angleValueb = analogRead(A1);
  data.finger= map(angleValueb,485,520,0,180);
  transmit.write(&data,sizeof(data));
  delay(200);                                 
}
