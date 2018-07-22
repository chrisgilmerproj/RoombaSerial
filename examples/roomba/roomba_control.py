#!/usr/bin/env python
import os
import sys
import serial
import time
import datetime

from optparse import OptionParser

#--- Declare the main program
if __name__ == '__main__':
    #--- Get the options from the command line
    usage = "usage: roomba_control [options]"
    parser = OptionParser(usage=usage)
    parser.add_option("-c", "--com",
                      dest="com",
                      default = "COM5",
                      type="string",
                      help="the COM port for the serial connection",
                      metavar="COM")
    parser.add_option("-b", "--baud",
                      dest="baud",
                      default=19200,
                      type="int",
                      help="the BAUD rate for the serial connection",
                      metavar="BAUD")
    parser.add_option("-t", "--timeout",
                      dest="timeout",
                      default=15,
                      type="int",
                      help="the TIMEOUT for the serial connection in seconds",
                      metavar="TIMEOUT")
    parser.add_option("-d", "--debug",
                      action="store_true",
                      dest="debug",
                      default=False,
                      help="turn on debug to print more information")
    (options, args) = parser.parse_args()

    DEBUG = False
    if options.debug:
        DEBUG = True

    #--- Set up the serial port to read from the Xbee
    SERIALPORT = options.com    # the com/serial port the XBee is connected to
    BAUDRATE = options.baud     # the baud rate we talk to the xbee
    TIMEOUT = options.timeout   # the timeout after which the readline will stop  
        
    #--- open up the FTDI serial port to get data transmitted to xbee
    ser = serial.Serial(SERIALPORT, BAUDRATE, timeout=TIMEOUT)
    ser.open()
    
    #--- Print the serial information once
    if DEBUG:
        print "PORT:\t\t%s\nBAUD:\t\t%s\nBYTESIZE:\t%s\nPARITY:\t\t%s\nSTOPBITS:\t%s\n" \
              %(ser.port, ser.baudrate, ser.bytesize, ser.parity, ser.stopbits)
    
    #--- Create the command to send to the arduino
    command = "COMMAND"
    if DEBUG:
        print "DEBUG"
    if command:
        ser.write(command)
    
    #--- Read in the data and split the line into words
    data = ser.readline()
