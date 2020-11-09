/*
Author:Mamadou BA Neige from MBA PRO TECH
Email: naedioba1@gmail.com   / mamadou.ba@ugb.edu.sn
Date: 11 November 2020
My YouTube Channel:https://www.youtube.com/channel/UCzC1VqRaFkubLkrMLdj2lmA
Title of video: How to Turn Off Your 3D Printer Automatically? / Comment arreter son imprimante 3D automatiquement ?
Link of video: https://youtu.be/gNGvbSk3R0k

This is a modified version of the system shown by LeGuëro Loco in his YouTube Channel.
I'm using an infra-red proximity sensor as a detector when the print job is done. Then
after 20 to 30 seconds, the printer turns off autimatically.

===👇Le GüeroLoco 👇===
Fermeture automatique de l'imprimante à moins de 5$ !
https://youtu.be/1jNsF7NxjuU

===👇Get the IR Proximity Sensor / Acheter le capteur IR👇===
from Banggood: https://www.banggood.com/search/ir-sensor.html?from=nav
from dealextreme: https://www.dx.com/p/ir-infrared-obstacle-avoidance-sensor-module-for-arduino-smart-car-robotg-2726126.html#.X6h6c2j7TIU

*/
#include <SoftwareSerial.h>
#include <Wire.h>

int relayOther = 3;             // pin for the relay of the other power socket
int relayEnder3Pro = 4;         // pin for the relay of socket where the Ender 3 Pro is pluged
int relayEnder3v2 = 5;          // pin for the relay of socket where the Ender 3 v2 is pluged
int relayLight = 6;             // pin for the relay of the socket for the light
 
int sensor_Ender3Pro = 7;       // pin of the IR sensor for the ender 3 Pro
int sensor_Ender3v2 = 8;        // pin of the IR sensor for the ender 3 v2

boolean stateSensor_Ender3Pro;  // state of the IR sensor for the ender 3 Pro
boolean stateSensor_Ender3v2;   // state of the IR sensor for the ender 3 v2

unsigned long initialTime_E3Pro = 0;  // initialization time for Ender 3 Pro
unsigned long initialTime_E3v2 = 0;   // initialization time for Ender 3 Pro

unsigned long currentMillis;

unsigned long previousMillisE3Pro = 0;    // previous millis for Ender 3 Pro
unsigned long previousMillisE3v2 = 0;     // previous millis for Ender 3 v2
unsigned long previousMillisLight = 0;    // previous millis for the light

unsigned long currentMillisE3Pro;         // current millis for Ender 3 Pro
unsigned long currentMillisE3v2;          // current millis for Ender 3 v2
unsigned long currentMillisLight;         // current millis for the light

long printer_TunOn_Confirmation = 10000;    // delay to confirm the state of the sensor to avoid untimely power on
long printer_TunOff_Confirmation = 30000;   // maximum delay to power off

//=========================
void setup() {

  Serial.begin(9600);
  
// setting up the relays pins a OUTPUT
  pinMode(relayOther,OUTPUT);
  pinMode(relayEnder3Pro,OUTPUT);
  pinMode(relayEnder3v2,OUTPUT);
  pinMode(relayLight,OUTPUT);

  // setting up tge sensors pins as INPUT
  pinMode(sensor_Ender3v2,INPUT);
  pinMode(sensor_Ender3Pro,INPUT);
  
// initial state of the relays
  digitalWrite(relayEnder3Pro, LOW);  // Ender 3 Pro turned off
  digitalWrite(relayEnder3v2, LOW);   // Ender 3 v2 turned off
  
  digitalWrite(relayOther, HIGH);     // other socket turned on
  digitalWrite(relayLight, HIGH);     // light turned on

// digital reading of sensors
  stateSensor_Ender3Pro = digitalRead(sensor_Ender3Pro);  
  stateSensor_Ender3v2 = digitalRead(sensor_Ender3v2);

} // end of setup
//=========================
void loop(){

// digital reading of sensors
  stateSensor_Ender3Pro = digitalRead(sensor_Ender3Pro);
  stateSensor_Ender3v2 = digitalRead(sensor_Ender3v2);

//++++++++++ FOR THE ENDER 3 PRO ++++++++++  
  if(stateSensor_Ender3Pro == HIGH){
    currentMillisE3Pro = millis();
    if(currentMillisE3Pro - previousMillisE3Pro >= printer_TunOn_Confirmation){
      stateSensor_Ender3Pro = digitalRead(sensor_Ender3Pro);
      if(stateSensor_Ender3Pro == HIGH){
        digitalWrite(relayEnder3Pro, HIGH);
        previousMillisE3Pro = currentMillisE3Pro;
      } 
    } 
  } 
  else 
  if(stateSensor_Ender3Pro == LOW){  
    currentMillisE3Pro = millis();
    if(currentMillisE3Pro - previousMillisE3Pro >= printer_TunOff_Confirmation){ 
      stateSensor_Ender3Pro = digitalRead(sensor_Ender3Pro);
      if(stateSensor_Ender3Pro == LOW){ 
        digitalWrite(relayEnder3Pro, LOW);
        previousMillisE3Pro = currentMillisE3Pro;
      } 
    } 
  } 

 //++++++++++ FOR THE ENDER 3 V2 ++++++++++ 
  if(stateSensor_Ender3v2 == HIGH){ 
    currentMillisE3v2 = millis();
    if(currentMillisE3v2 - previousMillisE3v2 >= printer_TunOn_Confirmation){ 
      stateSensor_Ender3v2 = digitalRead(sensor_Ender3v2);
      if(stateSensor_Ender3v2 == HIGH){ 
        digitalWrite(relayEnder3v2, HIGH);
        previousMillisE3v2 = currentMillisE3v2;
      } 
    } 
  } 
  else 
  if(stateSensor_Ender3v2 == LOW){  
    currentMillisE3v2 = millis();
    if(currentMillisE3v2 - previousMillisE3v2 >= printer_TunOff_Confirmation){ 
      stateSensor_Ender3v2 = digitalRead(sensor_Ender3v2);
      if(stateSensor_Ender3v2 == LOW){  
        digitalWrite(relayEnder3v2, LOW);
        previousMillisE3v2 = currentMillisE3v2;
      } 
    } 
  } 
 
 //++++++++++ FOR THE LIGHT AND OTHER SOCKET ++++++++++ 
// turned off if both printers are off  
      if(digitalRead(relayEnder3Pro) == LOW && digitalRead(relayEnder3v2) == LOW){
        digitalWrite(relayOther, LOW);
        digitalWrite(relayLight, LOW); 
      }

// turned on if at least one of the printers is on
  if(digitalRead(relayEnder3Pro) == HIGH || digitalRead(relayEnder3v2) == HIGH){
    digitalWrite(relayOther, HIGH);
    digitalWrite(relayLight, HIGH); 
  } 
} // end of loop
