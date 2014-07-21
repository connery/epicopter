#!/usr/bin/python3

from serial import Serial
import time
import sys

port = Serial('/dev/ttyACM0', 115200)
c = ''
rest = ""

if (port.isOpen() == 0):
        port.open()


if (port.isOpen()):
        port.write("!")
        while(port.inWaiting() == 0):
                time.sleep(0.5)

        while(1):
                sys.stdout.write(port.read())
                print("ret")
		sys.stdout.write(port.read())
		print("ret\n")
        
        
else:
    print("Port non ouvert")
