/*
  Robot.h - Library for controlling Robot Car with L298x bridge series
  Created by Oladapo E. Ajala, November 13, 2018.
  Released into the public domain.
  Copy right InvenTech llc.
*/

#include "Arduino.h"
#include "Robot.h"

#define DRIVE 1
#define REVERSE 2
#define PARK 3
#define GEAR_ERR 4
#define MAX_SPEED 1023
#define MIN_SPEED 200

uint16_t speed = MIN_SPEED;
uint8_t gearState = 4;

Robot::Robot(uint8_t IN1, uint8_t IN2, uint8_t IN3, uint8_t IN4)
{
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  _IN1 = IN1;
  _IN2 = IN2;
  _IN3 = IN3;
  _IN4 = IN4;
}

/*This function moves the robot depending on Gear & returns a true, if gear is not set it ensures robot doesn't move and returns false*/
bool Robot::move()
{
	if(gearState == DRIVE){
		analogWrite(_IN1, speed);
		analogWrite(_IN2, LOW);
		analogWrite(_IN3, speed);
		analogWrite(_IN4, LOW);  
		return true;
	}
	else if(gearState == REVERSE){
		analogWrite(_IN1, LOW);
		analogWrite(_IN2, speed);
		analogWrite(_IN3, LOW);
		analogWrite(_IN4, speed);  
		return true;
	}
	else if(gearState == PARK) {
		analogWrite(_IN1, LOW);
		analogWrite(_IN2, LOW);
		analogWrite(_IN3, LOW);
		analogWrite(_IN4, LOW);  
		return true;
	}
	else {
		analogWrite(_IN1, LOW);
		analogWrite(_IN2, LOW);
		analogWrite(_IN3, LOW);
		analogWrite(_IN4, LOW);  
		return false;
	}
}

/*Function to turn robot left, it returns a true upon completion*/
bool Robot::turnLeft()
{
	if(gearState == PARK || speed <= 250){
		analogWrite(_IN1, LOW);
		analogWrite(_IN2, LOW);
		analogWrite(_IN3, LOW);
		analogWrite(_IN4, LOW);  
		return false;
	}
	else{
		analogWrite(_IN1, speed);
		analogWrite(_IN2, LOW);
		analogWrite(_IN3, LOW);
		analogWrite(_IN4, speed);
		return true;
	}
}

/*Function to turn robot right, it returns a true upon completion */
bool Robot::turnRight()
{
	if(gearState == PARK || speed <= 250){
		analogWrite(_IN1, LOW);
		analogWrite(_IN2, LOW);
		analogWrite(_IN3, LOW);
		analogWrite(_IN4, LOW);  
		return false;
	}
	else{
		analogWrite(_IN1, LOW);
		analogWrite(_IN2, speed);
		analogWrite(_IN3, speed);
		analogWrite(_IN4, LOW);
		return true;
	}
}
/*This function reduces the speed of the robot by 5 every time it is called & returns the new speed*/
uint16_t Robot::brake()
{
	if(speed >= MIN_SPEED){
		speed-=50;
	}
	else {
		speed = MIN_SPEED;
	}
	
	analogWrite(_IN1, speed);
	analogWrite(_IN2, LOW);
	analogWrite(_IN3, speed);
	analogWrite(_IN4, LOW);
	
	return speed;
}

/*This function increases the speed of the robot by 5 every time it is called & returns the new speed*/
uint16_t Robot::accelerate()
{
	if(speed <= MAX_SPEED){
		speed+=50;
	}
	else {
		speed = MAX_SPEED;
	}
	analogWrite(_IN1, speed);
	analogWrite(_IN2, LOW);
	analogWrite(_IN3, speed);
	analogWrite(_IN4, LOW);
	
	return speed;
}

/*Gear function sets the gear of motor
*	1 -> Drive
*	2 -> Reverse
*	3 -> Park
*	4 -> Error
*/
uint8_t Robot::gear(uint8_t val)
{
	if(val == DRIVE || val == REVERSE || val == PARK){
		gearState = val;
		return gearState;
	}
	else { 
		return GEAR_ERR;
	}
}