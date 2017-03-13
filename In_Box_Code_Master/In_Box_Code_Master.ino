#include <Wire.h>
#include <stdio.h>
#include "Arduino.h"
#include <avr/eeprom.h>

const int anPin1 = 0;
const int anPin2 = 1;
const int anPin3 = 2;
const int anPin4 = 3;
int rPin = 6;
int gPin = 7;
int bPin = 8;
int distance1, distance2, distance3, distance4;
//int ledDistance[]{ 18, 40, 100, 180, 200 };
int ledDistance[]{ 12, 40, 300 };
int i = 0;

/* The first pin is red, second is green, third is blue
example;
ultrasonic1LEDpins[0] aka 2 == RED
ultrasonic1LEDpins[1] aka 3 == GREEN
ultrasonic1LEDpins[2] aka 4 == BLUE
*/

//int ultrasonic1LEDpins[3]{ 2, 3, 4 };
int ultrasonic1LEDpins[3]{ 2, 3, 4 }; //Test Code
int ultrasonic2LEDpins[3]{ 5, 6, 7 };
int laser1LEDpins[3]{ 8, 9, 10 };
int laser2LEDpins[3]{ 11, 12, 13 };

void setup() {
	Serial.begin(9600);
	//#############################################################################################################################################################################################################

	for (int i = 2; i < 14; i++) { // Unnecessary but fancy way of turning all the pins from 2 to 13 into output mode. **pin 15 is not set to output
		pinMode(i, OUTPUT);
	}

	//#############################################################################################################################################################################################################
	//for (int i = 14; i < 17; i++) {	//TEST CODE
	//	pinMode(i, OUTPUT);			//TEST CODE
}

void read_sensors() {
	distance3 = ((analogRead(anPin1) * 5) / 25.4);	//This is the formula for turning the 5v analog-in into inches to read by serial.
	distance4 = ((analogRead(anPin2) * 5) / 25.4);	//I could array these but its cleaner like this and I can quickly change the formula if I need to.
	distance1 = ((analogRead(anPin3) * 5) / 25.4);	//Ultrasonic
	distance2 = ((analogRead(anPin4) * 5) / 25.4);	//Ultrasonic
}
void print_all() {
	read_sensors();
	Serial.print("A"); Serial.println(distance1);
	Serial.print("B"); Serial.println(distance2);
	Serial.print("C"); Serial.println(distance2);
	Serial.print("D"); Serial.println(distance2);
	/*
	Serial.print("Ultrasonic Sensor 1 "); Serial.print(distance1); Serial.print(" in\t");
	Serial.print("Ultrasonic Sensor 2 "); Serial.print(distance2); Serial.print(" in\t");
	Serial.println(); // Next line in serial.
	Serial.print("Laser Sensor 1 "); Serial.print(distance3); Serial.print(" in\t");
	Serial.print("Laser Sensor 2 "); Serial.print(distance4); Serial.print(" in\t");
	*/
}
/* Each sensor needs 3 pins to change its color.
distance1 has 2, 3 & 4 ;
distance2 has 5, 6 & 7;
distance3 has 8, 9 & 10;
distance4 has 11, 12 & 13;
LED_color will detect which sensor has sensed an object and change its LED color accordingly.
*/
int LED_color(int x) {
	if (x == distance1) {
		return 1;
	}
	if (x == distance2) {
		return 2;
	}
	if (x == distance3) {
		return 3;
	}
	if (x == distance4) {
		return 4;
	}
	else {
		return 0;
	}
}
void setColor(int red, int green, int blue, int pinSet)
{
	/*          ##NOTE##
	pinSet 1 is ultrasonic 1 (distance1)
	pinSet 2 is ultrasonic 2 (distance2)
	pinSet 3 is laser 1 (distance3)
	pinSet 4 is laser 2 (distance4)
	*/
	switch (pinSet) {
	case 1:
		analogWrite(ultrasonic1LEDpins[0], red);
		analogWrite(ultrasonic1LEDpins[1], green);
		analogWrite(ultrasonic1LEDpins[2], blue);
		break;
	case 2:
		analogWrite(ultrasonic2LEDpins[0], red);
		analogWrite(ultrasonic2LEDpins[1], green);
		analogWrite(ultrasonic2LEDpins[2], blue);
		break;
	case 3:
		analogWrite(laser1LEDpins[0], red);
		analogWrite(laser1LEDpins[1], green);
		analogWrite(laser1LEDpins[2], blue);
		break;
	case 4:
		analogWrite(laser2LEDpins[0], red);
		analogWrite(laser2LEDpins[1], green);
		analogWrite(laser2LEDpins[2], blue);
		break;
	case 0:
		Serial.print("Serious problem! This case should never be seen and is for test purposes only!");
		break;
	}
}

void led_distance() {
	i++;
	if (i >= 4) {
		i = 0;
	}
	int distances[4] = { distance1, distance2, distance3, distance4 };
	if (distances[i] < ledDistance[2]) { // less than 100
		if (distances[i] < ledDistance[1]) {  //less than 50
			if (distances[i] < ledDistance[0]) { //less than 25
				setColor(255, 0, 0, LED_color(distances[i])); //This will set color to RED once I start using RGB LEDs.
				return;
			}
			setColor(0, 0, 255, LED_color(distances[i]));
			return;
		}
		setColor(0, 255, 0, LED_color(distances[i]));
	}
}

/*
	int distances[4] = { distance1, distance2, distance3, distance4 };
	if (distances[i] < ledDistance[4]) { //less than 200, as its impossible for these sensors to sense over 200 this will be the max distance
		if (distances[i] < ledDistance[3]) { //less than 180
			if (distances[i] < ledDistance[2]) { // less than 100
				if (distances[i] < ledDistance[1]) {  //less than 50
					if (distances[i] < ledDistance[0]) { //less than 25
						setColor(255, 0, 0, LED_color(distances[i])); //This will set color to RED once I start using RGB LEDs.
						return;
					}
					setColor(255, 255, 0, LED_color(distances[i]));
					return;
				}
				setColor(0, 255, 0, LED_color(distances[i]));
				return;
			}
			setColor(0, 0, 255, LED_color(distances[i]));
			return;
		}
		setColor(0, 255, 255, LED_color(distances[i]));
	}
}*/

void loop() {
	print_all();
	led_distance();
}

//Test