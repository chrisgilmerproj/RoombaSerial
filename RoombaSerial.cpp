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

// include core Wiring API
#include <WProgram.h>

// include this library's description file
#include "RoombaSerial.h"

// include description files for other libraries used (if any)
#include "NewSoftSerial.h"
#include <inttypes.h>

//==============================================================================
//==============================================================================
// Private Methods
// Functions only available to other functions in this library
//==============================================================================
//==============================================================================

//==============================================================================
//==============================================================================
// Constructor 
// Function that handles the creation and setup of instances
//==============================================================================
//==============================================================================
RoombaSerial::RoombaSerial(uint8_t rxPin, uint8_t txPin, uint8_t ddPin): 
  sciSerial(rxPin,txPin),
  _velocityLimit(500),
  _radiusLimit(2000)
{
  // initialize this instance's variables
  this->_rxPinRoomba = rxPin;
  this->_txPinRoomba = txPin;
  this->_ddPinRoomba = ddPin;

  // do whatever is required to initialize the library
  pinMode(this->_ddPinRoomba, OUTPUT);
  
}

//==============================================================================
//==============================================================================
// Public Methods 
// Functions available in Wiring sketches, this library, and other libraries
//==============================================================================
//==============================================================================
void RoombaSerial::init(void) {

  //--- Begin the serial port
  this->sciSerial.begin(57600);
  
  //--- wake up the robot
  this->wake();
  delay(100);

  //--- set up ROI to receive commands  
  this->start();
  delay(100);
  
  this->control();
  delay(100);

}

//==============================================================================
//==============================================================================
int16_t RoombaSerial::getVelocityLimit(void)
{
  return this->_velocityLimit;
}

//==============================================================================
int16_t RoombaSerial::getRadiusLimit(void)
{
  return this->_radiusLimit;
}

//==============================================================================
//==============================================================================
// Original code by Todbot
//==============================================================================
//==============================================================================
void RoombaSerial::goForward(void) {
  
  int velocity = 200;
  int radius = 32768;
  drive(velocity, radius); 

//  this->sciSerial.print(137, BYTE);   // DRIVE
//  this->sciSerial.print(0x00,BYTE);   // 0x00c8 == 200
//  this->sciSerial.print(0xc8,BYTE);
//  this->sciSerial.print(0x80,BYTE);
//  this->sciSerial.print(0x00,BYTE);
}

//==============================================================================
void RoombaSerial::goBackward(void) {
  
  int velocity = -200;
  int radius = 32768;
  drive(velocity, radius); 
  
  //this->sciSerial.print(137, BYTE);   // DRIVE
  //this->sciSerial.print(0xff,BYTE);   // 0xff38 == -200
  //this->sciSerial.print(0x38,BYTE);
  //this->sciSerial.print(0x80,BYTE);
  //this->sciSerial.print(0x00,BYTE);
}

//==============================================================================
void RoombaSerial::spinLeft(void) {
  
  int velocity = 200;
  int radius = 1;
  drive(velocity, radius); 
  
  //this->sciSerial.print(137, BYTE);   // DRIVE
  //this->sciSerial.print(0x00,BYTE);   // 0x00c8 == 200
  //this->sciSerial.print(0xc8,BYTE);
  //this->sciSerial.print(0x00,BYTE);
  //this->sciSerial.print(0x01,BYTE);   // 0x0001 == spin left
}

//==============================================================================
void RoombaSerial::spinRight(void) {
  
  int velocity = 200;
  int radius = -1;
  drive(velocity, radius); 
  
  //this->sciSerial.print(137, BYTE);   // DRIVE
  //this->sciSerial.print(0x00,BYTE);   // 0x00c8 == 200
  //this->sciSerial.print(0xc8,BYTE);
  //this->sciSerial.print(0xff,BYTE);
  //this->sciSerial.print(0xff,BYTE);   // 0xffff == -1 == spin right
}

//==============================================================================
void RoombaSerial::stopMoving(void) {
  
  int velocity = 0;
  int radius = 0;
  drive(velocity, radius); 
  
  //this->sciSerial.print(137, BYTE);   // DRIVE
  //this->sciSerial.print(0x00,BYTE);   // 0x0000 == 0
  //this->sciSerial.print(0x00,BYTE);
  //this->sciSerial.print(0x00,BYTE);
  //this->sciSerial.print(0x00,BYTE);   // 0x0000
}

//==============================================================================
//==============================================================================
// Roomba API Code
//==============================================================================
//==============================================================================
void RoombaSerial::wake(void) {
  digitalWrite(this->_ddPinRoomba, HIGH);
  delay(100);
  digitalWrite(this->_ddPinRoomba, LOW);
  delay(500);
  digitalWrite(this->_ddPinRoomba, HIGH);
  delay(2000);
}

//==============================================================================
void RoombaSerial::start(void) {
  this->sciSerial.print(128, BYTE);   // START
}

//==============================================================================
void RoombaSerial::setBaud(uint32_t baudRate) {
  this->sciSerial.print(129, BYTE);  // BAUD
  
  if(baudRate == 300) {
    this->sciSerial.print(0, BYTE);   // 300
  } else if(baudRate == 600) {
    this->sciSerial.print(1, BYTE);   // 600
  } else if(baudRate == 1200) {
    this->sciSerial.print(2, BYTE);   // 1200
  } else if(baudRate == 2400) {
    this->sciSerial.print(3, BYTE);   // 2400
  } else if(baudRate == 4800) {
    this->sciSerial.print(4, BYTE);   // 4800
  } else if(baudRate == 9600) {
    this->sciSerial.print(5, BYTE);   // 9600
  } else if(baudRate == 14400) {
    this->sciSerial.print(6, BYTE);   // 14400
  } else if(baudRate == 19200) {
    this->sciSerial.print(7, BYTE);   // 19200
  } else if(baudRate == 28800) {
    this->sciSerial.print(8, BYTE);   // 28800
  } else if(baudRate == 38400) {
    this->sciSerial.print(9, BYTE);   // 38400
  } else if(baudRate == 57600) {
    this->sciSerial.print(10, BYTE);  // 57600
  } else if(baudRate == 115200) {
    this->sciSerial.print(11, BYTE);  // 115200
  }
}

//==============================================================================
void RoombaSerial::control(void) {
  this->sciSerial.print(130, BYTE);   // CONTROL
}

//==============================================================================
void RoombaSerial::safe(void) {
  this->sciSerial.print(131, BYTE);   // SAFE
}

//==============================================================================
void RoombaSerial::full(void) {
  this->sciSerial.print(132, BYTE);   // FULL
}

//==============================================================================
void RoombaSerial::power(void) {
  this->sciSerial.print(133, BYTE);   // POWER
}

//==============================================================================
void RoombaSerial::spot(void) {
  this->sciSerial.print(134, BYTE);   // SPOT
}

//==============================================================================
void RoombaSerial::clean(void) {
  this->sciSerial.print(135, BYTE);   // CLEAN
}

//==============================================================================
void RoombaSerial::maxMode(void) {
  this->sciSerial.print(136, BYTE);   // MAX
}

//==============================================================================
void RoombaSerial::drive(int16_t velocity, int16_t radius) {

  //--- The high and low bytes sent to the roomba
  uint8_t v_byte_high;
  uint8_t v_byte_low;
  uint8_t r_byte_high;
  uint8_t r_byte_low;
  
  //--- Safe the velocity values and convert them
  if(velocity >= this->_velocityLimit) {
    velocity = this->_velocityLimit;
  } else if(velocity <= -this->_velocityLimit) {
    velocity = -this->_velocityLimit;
  }
  v_byte_low = velocity & 0xFF;
  v_byte_high = velocity >> 8;

  //--- Safe the radius values and convert them
  // Forward case
  if(radius == 32768 || radius == -32768) {
    r_byte_high = 128;
    r_byte_low = 0;
  } 
  // Counter-clockwise
  else if(radius == 1) {
    r_byte_high = 0;
    r_byte_low = 1;
  } 
  // Clockwise
  else if(radius == -1) {
    r_byte_high = 255;
    r_byte_low = 255;
  } 
  // General data
  else {
    if(radius >= this->_radiusLimit) {
      radius = this->_radiusLimit;
    } else if(radius <= -this->_radiusLimit) {
      radius = -this->_radiusLimit;
    }
    r_byte_low = radius & 0xFF;
    r_byte_high = radius >> 8;
  }

  this->sciSerial.print(137, BYTE);   // DRIVE
  this->sciSerial.print(v_byte_high, BYTE);
  this->sciSerial.print(v_byte_low,  BYTE);
  this->sciSerial.print(r_byte_high, BYTE);
  this->sciSerial.print(r_byte_low,  BYTE);
}

//==============================================================================
void RoombaSerial::motor(uint8_t motorNum) {
  
  if(motorNum >= 63) {
    motorNum = 63;
  }
  
  this->sciSerial.print(138, BYTE);   // MOTOR
  this->sciSerial.print(motorNum, BYTE);
}

//==============================================================================
void RoombaSerial::ledOn(uint8_t ledNum, uint8_t power, uint8_t color) {
  
  if(ledNum >= 63) {
    ledNum = 63;
  }
  
  this->sciSerial.print(139, BYTE);   // LED
  this->sciSerial.print(ledNum, BYTE);
  this->sciSerial.print(power, BYTE);
  this->sciSerial.print(color, BYTE);
}

//==============================================================================
//140 NO SONG API YET

//==============================================================================
void RoombaSerial::play(int songNum) {
  //--- Safe the song values
  if(songNum <= 0) {
    songNum = 0;
  } else if(songNum >= 15) {
    songNum = 15;
  }

  this->sciSerial.print(141, BYTE);   // PLAY
  this->sciSerial.print(songNum, BYTE);
}

//==============================================================================
//--- Modified Code by Todbot
void RoombaSerial::updateSensors(uint8_t sensorCode) {
  
  //--- Safe the sensor values
  if(sensorCode > 3) {
    sensorCode = 3;
  }
  
  this->sciSerial.print(142, BYTE);
  this->sciSerial.print(sensorCode,   BYTE);  // sensor packet 1, 10 bytes
  
  delay(100); // wait for sensors 
  
  char i = 0;
  while(this->sciSerial.available()) {
    int c = this->sciSerial.read();
    
    if(sensorCode == 0){
      this->_sensorbytes_0[i++] = c;
    }
    if(sensorCode == 1){
      this->_sensorbytes_1[i++] = c;
    }
    if(sensorCode == 2){
      this->_sensorbytes_2[i++] = c;
    }
    if(sensorCode == 3){
      this->_sensorbytes_3[i++] = c;
    }
  }
}

//==============================================================================
void RoombaSerial::forceDock(void) {
  this->sciSerial.print(143, BYTE);   // FORCE-SEEK-DOCK
}

//==============================================================================
//==============================================================================
char* RoombaSerial::getSensorData(uint8_t sensorCode)
{
  //--- Safe the sensor values
  if(sensorCode > 3) {
    sensorCode = 3;
  }
  
  if(sensorCode == 0){
    return this->_sensorbytes_0;
  }
  if(sensorCode == 1){
    return this->_sensorbytes_1;
  }
  if(sensorCode == 2){
    return this->_sensorbytes_2;
  }
  if(sensorCode == 3){
    return this->_sensorbytes_3;
  }
}

//==============================================================================
bool RoombaSerial::bumpright(void) {
  if(this->_sensorbytes_1[0] & 0x01){
    return true;
  }
  return false;
}

//==============================================================================
bool RoombaSerial::bumpleft(void) {
  if(this->_sensorbytes_1[0] & 0x02){
    return true;
  }
  return false;
}

//==============================================================================
bool RoombaSerial::wheelDropLeft(void)
{
  if(this->_sensorbytes_1[0] & 0x03){
    return true;
  }
  return false;
}

//==============================================================================
bool RoombaSerial::wheelDropRight(void)
{
  if(this->_sensorbytes_1[0] & 0x04){
    return true;
  }
  return false;
}

//==============================================================================
bool RoombaSerial::wheelDropCaster(void)
{
  if(this->_sensorbytes_1[0] & 0x05){
    return true;
  }
  return false;
}

//==============================================================================
bool RoombaSerial::wallDetect(void)
{
  if(this->_sensorbytes_1[1]){
    return true;
  }
  return false;
}

//==============================================================================
bool RoombaSerial::cliffLeft(void)
{
  if(this->_sensorbytes_1[2]){
    return true;
  }
  return false;
}

//==============================================================================
bool RoombaSerial::cliffFrontLeft(void)
{
  if(this->_sensorbytes_1[3]){
    return true;
  }
  return false;
}

//==============================================================================
bool RoombaSerial::cliffFrontRight(void)
{
  if(this->_sensorbytes_1[4]){
    return true;
  }
  return false;
}

//==============================================================================
bool RoombaSerial::cliffRight(void)
{
  if(this->_sensorbytes_1[5]){
    return true;
  }
  return false;
}

//==============================================================================
bool RoombaSerial::virtualWallDetect(void)
{
  if(this->_sensorbytes_1[6]){
    return true;
  }
  return false;
}
