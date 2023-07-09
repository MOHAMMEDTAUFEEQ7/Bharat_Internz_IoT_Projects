#include <LiquidCrystal.h> // Decleration the LCD header file
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //RS, E, D4, D5, D6, D7
const int IR = 6;
const int LED1 = 13; 


 void setup(){
  lcd.clear();
  lcd.begin(16,2);
  lcd.setCursor(3,0);
  lcd.print("IR Sensor");
  lcd.setCursor(0,1);
  lcd.print("MD.TAUFEEQ BASHA");
  delay(500);
  
}


void loop(){
   Sensor1();
   delay(500);
}
void Sensor1(){
int statusSensor1 = digitalRead (IR);
  
  if (statusSensor1 == 1){
    digitalWrite(LED1, HIGH); // LED HIGH
    lcd.setCursor(0,0);
    lcd.print("Vechicle Found");
    lcd.setCursor(1,1);
    lcd.print("No Parking Space");
  }
  
  else
  {
    digitalWrite(LED1, LOW); // LED LOW
    lcd.setCursor(0,0);
    lcd.print("Vehicle Not Found");
    lcd.setCursor(0,1);
    lcd.print("Vacant Space");
 
  }
}
