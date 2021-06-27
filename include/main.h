// Include all header files here.

#include <Arduino.h>

#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#include "ServoEasing.h"

ServoEasing Servo1;
ServoEasing Servo2;


// Macro definition.

#define BLYNK_PRINT Serial


#define R_1       D3 
#define R_2       D4  
#define L_1       D1
#define L_2       D2

#define BAT       A0

#define minSpeed 500
#define maxSpeed 1024

//#define midPoint 512


#define arm_1       D7
#define arm_2       D8
