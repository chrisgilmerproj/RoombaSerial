/*
 * Roomba 
 * --------------
 * Implement the RoombaSerial library to command the roomba with an arduino
 * 
 * Arduino pin 3 (RX) is connected to Roomba TXD
 * Arduino pin 4 (TX) is connected to Roomba RXD
 * Arduino pin 5      is conencted to Roomba DD
 * 
 * Created 30 November 2009
 * by Chris P. Gilmer <chris.gilmer@gmail.com>
 * http://blog.chrisgilmer.net/
 *
 * Modified 1 December 2009
 * - Included library/API for other roomba functions
 *
 * Modified 8 December 2009
 * - Added NewSoftSerial library to handle communications with roomba
 *   Found at http://arduiniana.org/libraries/NewSoftSerial/
 * 
 * Modified 9 December 2009
 * - Completed the checkout of the driveRoomba() method
 *   The roomba now wakes up and drives on its own
 * 
 * Modified 10 December 2009
 * - Completed transition of all roomba functions into a stand
 *   alone library that any project can use.
 */

//--- Include All Libraries
#include <NewSoftSerial.h> // Needed since it is referenced by RoombaSerial
#include <RoombaSerial.h>

//--- Arduino Onboard Serial Ports and Digital Pin
#define rxPin 3
#define txPin 4
#define ddPin 5

//--- Define an LED pin
#define ledPin 13

//--- Add the Roomba object
RoombaSerial roomba(rxPin,txPin,ddPin);

//--- Setup Code
void setup() {
  //--- Set the digital pins as outputs
  pinMode(ledPin, OUTPUT);

  //--- Turn on/off LED to indicate init function
  digitalWrite(ledPin, HIGH);
  roomba.init();
  digitalWrite(ledPin, LOW);
}

//--- Loop Code
void loop() {
  //--- Turn on/off LED to indicate sensor function
  digitalWrite(ledPin, HIGH);
  roomba.updateSensors();
  digitalWrite(ledPin, LOW);

  if(roomba.bumpleft()) {
    roomba.spinRight();
    delay(1000);
  }
  else if(roomba.bumpright()) {
    roomba.spinLeft();
    delay(1000);
  }

  roomba.goForward();
}

