/*
  Drive.h - Library for controlling Robot Car with L298x bridge series
  Created by Oladapo E. Ajala, November 13, 2018.
  Released into the public domain.
  Copy right InvenTech inc.
*/

#ifndef Robot_h
#define Robot_h

#include "Arduino.h"

class Robot
{
  public:
    Robot(uint8_t IN1, uint8_t IN2, uint8_t IN3, uint8_t IN4);
    bool move();
    bool turnRight();
    bool turnLeft();
    uint16_t brake();
	uint16_t accelerate();
	uint8_t gear(uint8_t val);
  private:
	uint8_t _IN1;
	uint8_t	_IN2;
	uint8_t _IN3;
	uint8_t _IN4;
};

#endif
