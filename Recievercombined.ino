//TempSensor
int Vout;//Output voltage for voltage divider
int LEDpin=3;
int Beta = 3380; //3380 Kelvin Beta (25/50)
int Ro = 10000; //Resistance at 25 C
int To= 298.15; //Temp kelvin at 25 C
int T;
float R2;  //Resistance of thermistor
float R1=10000; //Known resistor value you put in with thermistor should be close to same value as thermistor
float Rfinity= Ro*exp(-(Beta/To));


//Reciever
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <Servo.h>

int thumb;
int finger;

bool button_1_new;
bool button_2_new;
bool button_3_new;
bool button_1_old = LOW;
bool button_2_old = LOW;
bool button_3_old = LOW; 
const int Button1 = 12;
const int Button2 = 11;
const int Button3 = 10;
float stop1;
float stop2;
float stop3;

RF24 receive (49,48); //ce and csn                      
const byte address [5] = {"00001"};

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

struct package
  {
    float thumb = 0;
    float finger = 0;
  };

typedef struct package Package;
Package data;

void setup() {
  //Reciever
  Serial.begin(9600);
  receive.begin();
  receive.openReadingPipe(0,address);      
  receive.setPALevel(RF24_PA_MIN);        
  receive.setDataRate(RF24_250KBPS);      
  receive.setChannel(100);                
  receive.startListening(); 

  servo1.attach(13); //finger 1 need pwm pins
  servo2.attach(12); //finger 2
  servo3.attach(11); //finger 3
  servo4.attach(10); //finger 4
  servo5.attach(9); //Thumb

  //TempSensor
pinMode(37,OUTPUT); //Need to set pins
pinMode(34,OUTPUT);
pinMode(35,OUTPUT);
  }

void loop() {
  //Reciever
  if (receive.available())                //check when received data available
  {
    receive.read(&data, sizeof(data));
    thumb=data.thumb;
    finger=data.finger;


    button_1_new=digitalRead(Button1);
    button_2_new=digitalRead(Button2);
    button_3_new=digitalRead(Button3);
    
    if(button_1_new==!button_1_old){
      stop1=finger;
    }
    if(button_2_new==!button_2_old){
      stop2=finger;
    }    
    if(button_3_new==!button_3_old){
      stop3=finger;
    }

    button_1_old=button_1_new;
    button_2_old=button_2_new;
    button_3_old=button_3_new;

    if(button_1_new==LOW){
    servo1.write(finger);
    servo2.write(finger);
    }
    else if(finger<stop1){
      servo1.write(finger);
      servo2.write(finger);
      button_1_old=LOW;    }
    else{
    servo1.write(stop1);
    servo2.write(stop1);
    }

    if(button_2_new==LOW){
    servo3.write(finger);
    servo4.write(finger);
    }
    else if(finger<stop2){
      servo3.write(finger);
      servo4.write(finger);
      button_2_old=LOW;    }
    else{
    servo3.write(stop2);
    servo4.write(stop2);
    }

    if(button_3_new==LOW){
    servo5.write(thumb);
    }
    else if(thumb<stop3){
    servo5.write(thumb);
    button_3_old=LOW;    }
    else{
    servo5.write(stop3);
    }
  }
  delay(100);


 //TempSensor
  TempSensor();
 //Serial.print("Temperature: "); //Debugging
  //Serial.print(T);
  //Serial.println("C"); //Debugging
}


void TempSensor() {
   Vout = analogRead(A0);
  R2 = R1 * (1023.0 / (float)Vout - 1.0); // R1 * (5V/ voltage bewteen resistors and thermistor -1)
 
  T = (Beta/log(R2/Rfinity)); //Beta eqn to convert resistance to temp
  
  T = T-273.15;
   
  
  if (T>30) {
  analogWrite(3,255); 
  
}
  
  else if (T>50) {
  analogWrite(9,255);
  }

  else if (T<0) {
  analogWrite(10,255);
  }
  }
