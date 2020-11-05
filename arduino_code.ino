#include <Servo.h>
#include <NewPing.h>
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
  lcd.begin(16, 2);
}

void loop() {

// This first block is dedicated to the servo
 /* for (pos = 0; pos <= 180; pos += 1){
    myservo.write(pos);       //instructions telling servo to go to pos
    delay(15);                //delay in ms
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
  */

// This second block is dedicated to the water level sensor
  int value = analogRead(adc_id); // get adc value

    if(((HistoryValue>=value) && ((HistoryValue - value) > 10)) || ((HistoryValue<value) && ((value - HistoryValue) > 10)))
    {
      sprintf(printBuffer,"ADC%d level is %d\n",adc_id, value);
      Serial.print(printBuffer);
      HistoryValue = value;
    }
  
  //the following if statement instructs the servo to move to 30 degrees if the value read by the sensor is greater than 0
  if(value > 100){
    myservo.write(30);
  }

// Third block for temperature sensor
   // setting the pin for the thermometer
   int tempReading = analogRead(tempPin);
     // variables for conversion
    //  Calibrate input to temperature in Kelvin
    double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK ); 
    // converting kelvin to celsius
    float tempC = tempK - 273.15;
    // converting celsius to Fahrenheit
    float tempF = (tempC * 9.0)/ 5.0 + 32.0;

    // if LCD display for temperature, use the below block
    /*lcd.setCursor(0, 0);
    lcd.print("Temp         C  ");
    // Display Temperature in F
    lcd.print("Temp         F  ");
    lcd.setCursor(6, 0);
    // Display Temperature in C
    lcd.print(tempC);
    // Display Temperature in F
    lcd.print(tempF);
    delay(500);
  */
  
}
