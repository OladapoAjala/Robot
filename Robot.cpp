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
//Maximum possible voltage level that can be written by InventOne
#define MAX_SPEED 1000
//Anything less than 200 won't move the motors
#define MIN_SPEED 100

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

/*This function moves the robot depending on Gear & returns speed, if gear is not set it ensures robot doesn't move.*/
uint16_t Robot::move()
{
	if(gearState == DRIVE){
		analogWrite(_IN1, speed);
		analogWrite(_IN2, LOW);
		analogWrite(_IN3, speed);
		analogWrite(_IN4, LOW);  
		return speed;
	}
	else if(gearState == REVERSE){
		analogWrite(_IN1, LOW);
		analogWrite(_IN2, speed);
		analogWrite(_IN3, LOW);
		analogWrite(_IN4, speed);  
		return speed;
	}
	else if(gearState == PARK) {
		analogWrite(_IN1, LOW);
		analogWrite(_IN2, LOW);
		analogWrite(_IN3, LOW);
		analogWrite(_IN4, LOW);  
		return speed;
	}
	else {
		analogWrite(_IN1, LOW);
		analogWrite(_IN2, LOW);
		analogWrite(_IN3, LOW);
		analogWrite(_IN4, LOW);  
		return speed;
	}
}

/*Function to turn robot left, it returns speed upon completion*/
uint16_t Robot::turnLeft()
{
	if(gearState == PARK || speed <= MIN_SPEED){
		analogWrite(_IN1, LOW);
		analogWrite(_IN2, LOW);
		analogWrite(_IN3, LOW);
		analogWrite(_IN4, LOW);  
		return speed;
	}
	else{
		analogWrite(_IN1, speed);
		analogWrite(_IN2, LOW);
		analogWrite(_IN3, LOW);
		analogWrite(_IN4, speed);
		return speed;
	}
}

/*Function to turn robot right, it returns speed upon completion */
uint16_t Robot::turnRight()
{
	if(gearState == PARK || speed <= MIN_SPEED){
		analogWrite(_IN1, LOW);
		analogWrite(_IN2, LOW);
		analogWrite(_IN3, LOW);
		analogWrite(_IN4, LOW);  
		return speed;
	}
	else{
		analogWrite(_IN1, LOW);
		analogWrite(_IN2, speed);
		analogWrite(_IN3, speed);
		analogWrite(_IN4, LOW);
		return speed;
	}
}
/*This function reduces the speed of the robot by 5 every time it is called & returns the new speed*/
uint16_t Robot::brake()
{
	if(speed > MIN_SPEED){
		speed-=50;
	}
	else {
		speed = MIN_SPEED;
	}
	move();
}

/*This function increases the speed of the robot by 5 every time it is called & returns the new speed*/
uint16_t Robot::accelerate()
{
	if(speed < MAX_SPEED){
		speed+=50;
	}
	else {
		speed = MAX_SPEED;
	}
	move();
}

/*Gear function sets the gear of motor
*	1 -> Drive
*	2 -> Reverse
*	3 -> Park
*	4 -> Error
*Handle unhealthy gear changes, like reverse to drive without braking to zero....
*/
uint8_t Robot::gear(uint8_t val)
{
	if(val == DRIVE || val == REVERSE || val == PARK){
		//If you try to park when speed is not minimum speed return an error: Might want to edit this to automatically call brake.
		if(speed != MIN_SPEED && val == PARK){
			while(speed != MIN_SPEED){
				brake();
				delay(100);
			}
			move();
			return gearState;
		}
		//If you are moving forward and you try to reverse without braking to zero, call brake function automatically
		else if(gearState == DRIVE && speed != MIN_SPEED && val == REVERSE){
			while(speed != MIN_SPEED){
				brake();
				delay(100);
			}
			gearState = val;
			move();
			return gearState;
		}
		//If you are moving backwards and you try to drive without braking to zero, call brake function automatically
		else if(gearState == REVERSE && speed != MIN_SPEED && val == DRIVE){
			while(speed != MIN_SPEED){
				brake();
				delay(100);
			}
			gearState = val;
			move();
			return gearState;
		}
		gearState = val;
		move();
		return gearState;
	}
	else { 
		return GEAR_ERR;
	}
}