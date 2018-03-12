//Set thermistor up with a 10K resistor NTC 
//Refer to http://www.circuitbasics.com/arduino-thermistor-temperature-sensor-tutorial/
//Use Steinhart equation to convert resistance to temperature

int Tinputpin = 0;
int Vout;
int LEDpin=5;
float R1 = 10000; //Resistor value
float logR2, R2, T;
float c1 = , c2 = , c3 = ; //Coefficients of thermistor

void setup() {
Serial.begin(9600); //For debugging and testing temp sensor readings
pinMode(5,OUTPUT); //Digital pin PWM

}

void loop() {

  Vo = analogRead(Tinputpin);
  R2 = R1 * (1023.0 / (float)Vout - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); //Stein-hart eqn to convert resistance to temp
  T = T - 273.15;
 
  Serial.print("Temperature: "); //Debugging
  Serial.print(T);
  Serial.println("C"); //Debugging
  delay(500);
  
  if (T>40) {           //If temperature exceeds 40 degrees celcius
  analogWrite(5,T+100); //PWM +100 up to 255 at max (can set any number here)
  }
}