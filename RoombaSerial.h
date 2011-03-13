/*
  RoombaSerial.h - Commands to be sent to the Roomba Serial Interface
  Copyright (c) 2009 Chris P. Gilmer.  All right reserved.
  
  - Reference iRobot(R) Roomba(R) Serial Command Interface (SCI) Specification
    http://www.irobot.com/
  
  - Based upon RoombaBumpTurn code by Tod E. Kurt <tod@todbot.com>
    http://hackingroomba.com/
    Created 1 August 2006 (copyleft 2006) 
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

// ensure this library description is only included once
#ifndef RoombaSerial_h
#define RoombaSerial_h

// include types & constants of Wiring core API and other libraries
#include "WConstants.h"
#include "NewSoftSerial.h"
#include <inttypes.h>

// define roomba specific variables
#define _ROOMBASERIAL_VERSION 1 // software version of this library

// library interface description
class RoombaSerial
{

  // library-accessible "private" interface
  private:
    
    //--- Roomba Pins
    uint8_t _rxPinRoomba;
    uint8_t _txPinRoomba;
    uint8_t _ddPinRoomba;
    
    //--- Limits
    int16_t _velocityLimit;
    int16_t _radiusLimit;
    
    //--- Roomba sensor bytes
    char _sensorbytes_0[26];
    char _sensorbytes_1[10];
    char _sensorbytes_2[6];
    char _sensorbytes_3[10];
  
  // user-accessible "public" interface
  public:
    
    //--- Serial Connection to Roomba
    NewSoftSerial sciSerial;
    
    //--- Roomba Serial Constructor
    RoombaSerial(uint8_t rxPin, uint8_t txPin, uint8_t ddPin);
    
    //--- Custom Roomba Functions
    void init(void);
    int16_t getVelocityLimit(void);
    int16_t getRadiusLimit(void);
    
    //--- Original Code by Todbot
    void goForward(void);
    void goBackward(void);
    void spinLeft(void);
    void spinRight(void);
    void stopMoving(void);
    
    //--- Roomba Serial Functions
    void wake(void);
    void start(void);
    void setBaud(uint32_t baudRate);
    void control(void);
    void safe(void);
    void full(void);
    void power(void);
    void spot(void);
    void clean(void);
    void maxMode(void);
    void drive(int16_t velocity, int16_t radius);
    void motor(uint8_t motorNum);
    void ledOn(uint8_t ledNum, uint8_t power, uint8_t color);
    //140 NO SONG API YET
    void play(int songNum);
    void updateSensors(uint8_t sensorCode = 1);
    void forceDock(void);
    
    //--- Sensor Functions
    char* getSensorData(uint8_t sensorCode = 1);
    bool bumpright(void);
    bool bumpleft(void);
    bool wheelDropLeft(void);
    bool wheelDropRight(void);
    bool wheelDropCaster(void);
    bool wallDetect(void);
    bool cliffLeft(void);
    bool cliffFrontLeft(void);
    bool cliffFrontRight(void);
    bool cliffRight(void);
    bool virtualWallDetect(void);
};

// Arduino 0012 workaround
#undef int
#undef char
#undef long
#undef byte
#undef float
#undef abs
#undef round 

#endif

