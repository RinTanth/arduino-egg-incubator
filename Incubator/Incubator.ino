#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 4
#define Type DHT11

int sensePin = 4;
DHT HT(sensePin,Type);
float h;
float t;
float ttemp;
float htemp;
const int ok = A1;
const int UP = A2;
const int DOWN = A3;

const int bulb = 3;
const int vap = 6;

const int rs = 8;
const int en = 9;
const int d4 = 10;
const int d5 = 11;
const int d6 = 12;
const int d7 = 13;

int ack = 0;
int pos = 0;
int sec = 0;
int Min = 0;
int hrs = 0;
float T_threshold_high = 37.5;
float T_threshold_low = 36.5;
int H_threshold_high = 65;
int H_threshold_low = 50;
int SET = 0;
int Direction = 0;
boolean T_condition = true;
boolean H_condition = true;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup()
{
  pinMode(ok, INPUT); //A1
  pinMode(UP, INPUT); //A2
  pinMode(DOWN, INPUT); //A3
  pinMode(bulb, OUTPUT);  //3
  pinMode(vap, OUTPUT); //6
  digitalWrite(bulb, LOW);
  digitalWrite(vap, LOW);
  digitalWrite(ok, HIGH);
  digitalWrite(UP, HIGH);
  digitalWrite(DOWN, HIGH);

  lcd.begin();
  Serial.begin(9600);
  HT.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature &");
  lcd.setCursor(0, 1);
  lcd.print("Humidity ");
  delay (1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Controller For");
  lcd.setCursor(0, 1);
  lcd.print("Incubator");
  delay (1000);
  lcd.clear();
  Serial.println("  Temperature and Humidity Controller For Incubator");
}
void loop()
{
    t = HT.readTemperature();
    if(!isnan(t)){
      ttemp = t;
    }
    else{
      Serial.println(ttemp);
    }
    
    delay(2000);

    h = HT.readHumidity();
    if(!isnan(h)){
      htemp = h;
    }
    else{
    }
    delay(2000);

  
  ack = 0;
  int chk;
  chk = HT.read(DHTPIN);    // READ DATA

  Serial.print("DHT11, \t");
  Serial.print(t, 1);
  Serial.print(",\t");
  Serial.println(h, 1);
  delay(100);

  if (ack == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tempurature:");
    lcd.print(t);
    lcd.setCursor(0, 1);
    lcd.print("Humidity:");
    lcd.print(h);
    delay(2000);
    if (t >= T_threshold_high)
    {
      delay(100);
      if (t >= T_threshold_high)
      {
        digitalWrite(bulb, LOW);  
        digitalWrite(vap, LOW); //i move fan here to 
        Serial.println("Light off");
        Serial.println("fan low");
      }
    }
    if (h >= H_threshold_high)
    {
      delay(100);
      if (h >= H_threshold_high)
      {
        //digitalWrite(vap, HIGH);
      }
    }
    if (t < T_threshold_low)
    {
      delay(100);
      if (t < T_threshold_low)
      {
        digitalWrite(bulb, HIGH);
        digitalWrite(vap, HIGH); //i move fan here to check
        Serial.println("Light on");
        Serial.println("fan high");
      }
    }
    if (h < H_threshold_low)
    {
      delay(100);
      if (h < H_threshold_low)
      {
        //digitalWrite(vap, LOW);
      }
    }
  }
  if (ack == 1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("No Sensor data.");
    lcd.setCursor(0, 1);
    lcd.print("System Halted.");
    digitalWrite(bulb, LOW);
    digitalWrite(vap, LOW);
  }
  delay(100);
}
