//Set thermistor up with a 10K resistor NTC 
//Refer to http://www.circuitbasics.com/arduino-thermistor-temperature-sensor-tutorial/
//https://electronics.stackexchange.com/questions/105682/thermistor-calculations-using-b-parameter-equation
//Use Beta Equation to convert resistance to temperature


int Vout;//Output voltage for voltage divider
int LEDpin=3;
int Beta = 3380; //3380 Kelvin Beta (25/50)
int Ro = 10000; //Resistance at 25 C
int To= 298.15; //Temp kelvin at 25 C
int T;
float R2;  //Resistance of thermistor
float R1=10000; //Known resistor value you put in with thermistor should be close to same value as thermistor
float Rfinity= Ro*exp(-(Beta/To));


void setup() {
Serial.begin(9600); //For debugging and testing temp sensor readings
pinMode(3,OUTPUT); //Digital pin PWM
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);

}

void loop() {

  Vout = analogRead(A0);
  R2 = R1 * (1023.0 / (float)Vout - 1.0); // R1 * (5V/ voltage bewteen resistors and thermistor -1)
 
  T = (Beta/log(R2/Rfinity)); //Beta eqn to convert resistance to temp
  
  T = T-273.15;
 
  Serial.print("Temperature: "); //Debugging
  Serial.print(T);
  Serial.println("C"); //Debugging
  delay(500);
  
  
  if (T>30) {
  analogWrite(3,255); 
  
}
  
  elseif (T>50) {
  analogWrite(9,255);
  }

  elseif(T<0) {
  analogWrite(10,255);
  }
  
  
  }
  

