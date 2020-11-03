#include <Servo.h>

#include <LiquidCrystal.h>

//servo vars
Servo myservo;
int pos = 0; 

//depth vars
int adc_id = 0;
int HistoryValue = 0;
char printBuffer[128];

//temperature vars


void setup() {
//servo set up
myservo.attach(9); // the 9 represents what pin the servo is in

//depth set up
Serial.begin(9600);  //mostly just starting serial monitor, not really specific to depth

//temperature set up

}

void loop() {

// This first block is dedicated to the servo
  for (pos = 0; pos <= 180; pos += 1){
    myservo.write(pos);       //instructions telling servo to go to pos
    delay(15);                //delay in ms
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(15);                       
  }

// This second block is dedicated to the water level sensor
  int value = analogRead(adc_id); // get adc value

    if(((HistoryValue>=value) && ((HistoryValue - value) > 10)) || ((HistoryValue<value) && ((value - HistoryValue) > 10)))
    {
      sprintf(printBuffer,"ADC%d level is %d\n",adc_id, value);
      Serial.print(printBuffer);
      HistoryValue = value;
    }

// Third block for temperature sensor


}
