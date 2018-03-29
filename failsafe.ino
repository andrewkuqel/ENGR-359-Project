#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;

int input;
void setup()
{
  myservo1.attach(2);
  myservo2.attach(3);
  myservo3.attach(4);
  myservo4.attach(5);
  myservo5.attach(6);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.read();
    Serial.println(input);
    delay (2000);
  }
  if(input=='w'){
  myservo1.write(180);
  myservo2.write(0);
  myservo3.write(0);
  myservo4.write(180);
  myservo5.write(180);
  }
    if(input=='q'){
  myservo1.write(0);
  myservo2.write(180);
  myservo3.write(0);
  myservo4.write(180);
  myservo5.write(180);
  }
    if(input=='e'){
  myservo1.write(0);
  myservo2.write(0);
  myservo3.write(180);
  myservo4.write(180);
  myservo5.write(180);
  }
    if(input=='r'){
  myservo1.write(0);
  myservo2.write(0);
  myservo3.write(0);
  myservo4.write(0);
  myservo5.write(180);
  }
      if(input==' '){
  myservo1.write(0);
  myservo2.write(0);
  myservo3.write(0);
  myservo4.write(180);
  myservo5.write(0);
  }
} 
