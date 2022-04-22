 #include <Wire.h>
#include <TimerOne.h>
#include <LiquidCrystal_I2C.h>

const unsigned long duration = 2000000;   // Duration of display for 1 mode
volatile int modeSelect = 0;              // Index of modes array   
int modeSelectCopy = 0;                   // Copy of Index of modes array

//Sun Icon
byte sun1[8] = {B00000, B00000, B00000, B00010, B00000, B00000, B00000, B01110};
byte sun2[8] = {B00000, B00100, B00100, B00100, B00000, B01110, B11101, B11111};
byte sun3[8] = {B00000, B00000, B00000, B01000, B00000, B00000, B00000, B01110};
byte sun4[8] = {B00000, B00000, B00000, B00010, B00000, B00000, B00000, B00000};
byte sun5[8] = {B11111, B01110, B00000, B00100, B00100, B00100, B00000, B00000};
byte sun6[8] = {B00000, B00000, B00000, B01000, B00000, B00000, B00000, B00000}; 

LiquidCrystal_I2C lcd(0x27, 16, 2);
String modes[5] = {"Temperature", "Soil Moisture", "Air Quality", "Air Humidity", "Sunlight"};  // Modes for LCD display

void displayMode(int i) {
  lcd.clear();      
  delay(500);   // Small delay before displaying the mode
  // lcd.print(modes[i]);
  lcd.write(0);
  lcd.write(1);
  lcd.write(2);

  lcd.setCursor(0, 1);
  lcd.write(3);
  lcd.write(4);
  lcd.write(5);
}


void setup(void) {
  lcd.begin();
  lcd.backlight();
  displayMode(modeSelect);
  Timer1.initialize(duration);
  Timer1.attachInterrupt(changeMode);
  lcd.createChar(0, sun1);
  lcd.createChar(1, sun2);
  lcd.createChar(2, sun3);
  lcd.createChar(3, sun4);
  lcd.createChar(4, sun5);
  lcd.createChar(5, sun6);
  
}


void changeMode(void) { // Timer1 Interrupt (2 Seconds)
  modeSelect = modeSelect + 1;
  
  if (modeSelect > 4) { // If the pointer is over the length of modes array
    modeSelect = 0;
  }
}

void loop(void) {
  if (modeSelect != modeSelectCopy) {   // Move to the next mode is the modeSelect does not equal its copy
    displayMode(modeSelect);            // Update the display to the next mode
    modeSelectCopy = modeSelect;        
  }

} 
