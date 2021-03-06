/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.


*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;
void setup() {
  Serial.begin(9600);
  pinMode(8,INPUT);
  starttime = millis();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Initializing...");
}
void loop() {
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;

  if ((millis()-starttime) > sampletime_ms)
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Concentration = ");
    lcd.setCursor(0,1);
    lcd.print(concentration);
    if (concentration<1000){
      delay(2000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Pristine");
      delay(2000);
      lcd.clear();
      lcd.print("Initializing...");
      lowpulseoccupancy = 0;
      starttime = millis();}
}
// if error in code, than below this line or power cords(except the part where the numebers are weird, check indents of the first if statement and below)
    if (concentration >= 1000 && concentration < 10000){
      delay(2000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Clean");
      delay(2000);
      lcd.clear();
      lcd.print("Initializing...");
      lowpulseoccupancy = 0;
      starttime = millis();} 

    if (concentration >= 10000 && concentration < 20000){
      delay(2000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Acceptable");
      delay(2000);
      lcd.clear();
      lcd.print("Initializing...");
      lowpulseoccupancy = 0;
      starttime = millis();}  

    if (concentration >= 20000 && concentration < 50000){
      delay(2000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Heavy");
      delay(2000);
      lcd.clear();
      lcd.print("Initializing...");
      lowpulseoccupancy = 0;
      starttime = millis();}  

     if (concentration>=50000){
      delay(2000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Hazard");
      delay(2000);
      lcd.clear();
      lcd.print("Initializing...");
      lowpulseoccupancy = 0;
      starttime = millis();}  

    
    
} 
