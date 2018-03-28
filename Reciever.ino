#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <Servo.h>

int thumb;
int finger;

RF24 receive (7,8);                         
const byte address [5] = {"00001"};

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

struct package
  {
    float thumb = 0;
    float temp = 0;
  };

typedef struct package Package;
Package data;

void setup() {
  Serial.begin(9600);
  receive.begin();
  receive.openReadingPipe(0,address);      
  receive.setPALevel(RF24_PA_MIN);        
  receive.setDataRate(RF24_250KBPS);      
  receive.setChannel(100);                
  receive.startListening(); 

  servo1.attach(9); //finger 1 need pwm pins
  servo2.attach(6); //finger 2
  servo3.attach(5); //finger 3
  servo4.attach(10); //finger 4
  servo5.attach(3); //Thumb
  }

void loop() {

  if (receive.available())                //check when received data available
  {
    receive.read(&data, sizeof(data));
    thumb=data.thumb;
    finger=data.temp;
    servo1.write(finger);
    servo2.write(finger);
    servo3.write(finger);
    servo4.write(finger);
    servo5.write(thumb);
    
    
  }
  delay(100);
    
}

void hello(){

}
}

