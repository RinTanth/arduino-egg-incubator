/*
 * Arduino code to control AC bulb with relay
 * 
 * 
 * Written by Ahmad Shamshiri for Robojax.com on Saturday August 17, 2019 
 * at 16:27 in Ajax, Ontario, Canada
 * Watch video instruction 
 * for this code: https://youtu.be/g6k8sPJyif8
 * 
 * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.* 
 * This code has been download from Robojax.com
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see .
 */


int relayPin = 3;
int loopDelay = 1000;// delay in loop


void setup() {

    pinMode(relayPin, OUTPUT);// set pin as output
    digitalWrite(relayPin, LOW); // set initial state OFF for low trigger relay


  
  Serial.begin(9600);// initialize serial monitor with 9600 baud
  Serial.println("Robojax Relay Control- AC bulb");
  delay(2000);
}

void loop() {
  // Robojax AC load control with 5V relay
 // turn relay ON
  digitalWrite(relayPin, HIGH);
  Serial.println("Relay is ON");  
  delay(2000);// wait for 2 seconds


 // turn relay OFF
  digitalWrite(relayPin, LOW);
  Serial.println("Relay is OFF");   
  delay(2000);// wait for 2 seconds
 
  
 Serial.println("===============");

 delay(loopDelay);// wait for loopDelay ms
          
}// loop end
