#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include <DHT.h>
DHT dht(4 , DHT11);
#define DHTPIN 4
#define DHTTYPE DHT11

float h = dht.readHumidity();
float t = dht.readTemperature();
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
int T_threshold_high = 38;
int T_threshold_low = 35;
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

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature &");
  lcd.setCursor(0, 1);
  lcd.print("Humidity ");
  delay (3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Controller For");
  lcd.setCursor(0, 1);
  lcd.print("Incubator");
  delay (3000);
  lcd.clear();
  Serial.println("  Temperature and Humidity Controller For Incubator");
}
void loop()
{

  if (SET == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Temperature:");
    lcd.setCursor(0, 1);
    //lcd.print(T_threshold);
    lcd.print(" *C");
    while (T_condition)
    {
      if (digitalRead(UP) == LOW)
      {
        //T_threshold = T_threshold + 1;
        lcd.setCursor(0, 1);
        //lcd.print(T_threshold);
        lcd.print(" *C");
        delay(200);
      }
      if (digitalRead(DOWN) == LOW)
      {
        //T_threshold = T_threshold - 1;
        lcd.setCursor(0, 1);
        //lcd.print(T_threshold);
        lcd.print(" *C");
        delay(200);
      }
      if (digitalRead(ok) == LOW)
      {
        delay(200);
        T_condition = false;
      }
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Humidity:");
    lcd.setCursor(0, 1);
    //lcd.print(H_threshold);
    lcd.print("%");
    delay(100);
    while (H_condition)
    {
      if (digitalRead(UP) == LOW)
      {
        //H_threshold = H_threshold + 1;
        lcd.setCursor(0, 1);
        //lcd.print(H_threshold);
        lcd.print("%");
        delay(100);
      }
      if (digitalRead(DOWN) == LOW)
      {
        //H_threshold = H_threshold - 1;
        lcd.setCursor(0, 1);
        //lcd.print(H_threshold);
        lcd.print("%");
        delay(200);
      }
      if (digitalRead(ok) == LOW)
      {
        delay(100);
        H_condition = false;
      }
    }
    SET = 1;
  }
  ack = 0;
  int chk;
  //dht.read11(DHTPIN);
  chk = dht.read(DHTPIN);    // READ DATA

  Serial.print("DHT11, \t");
  Serial.print(t, 1);
  Serial.print(",\t");
  Serial.println(h, 1);
  delay(100);

  if (ack == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(t);
    lcd.setCursor(0, 1);
    lcd.print("Humidity:");
    lcd.print(h);
    delay(500);
    if (t >= T_threshold_high)
    {
      delay(500);
      if (t >= T_threshold_high)
      {
        digitalWrite(bulb, LOW);
      }
    }
    if (h >= H_threshold_high)
    {
      delay(500);
      if (h >= H_threshold_high)
      {
        digitalWrite(vap, HIGH);
      }
    }
    if (t < T_threshold_low)
    {
      delay(500);
      if (t < T_threshold_low)
      {
        digitalWrite(bulb, HIGH);
      }
    }
    if (h < H_threshold_low)
    {
      delay(500);
      if (h < H_threshold_low)
      {
        digitalWrite(vap, LOW);
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
  delay(500);
}
