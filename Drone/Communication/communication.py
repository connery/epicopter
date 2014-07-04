#!/usr/bin/python3

from serial import Serial
import time
import sys

port = Serial('/dev/ttyACM0', 115200)
print(port.name)
c = ''
rest = ""

if (port.isOpen() == 0):
        port.open()


if (port.isOpen()):
        time.sleep(5)
        print("go\n")
        port.write("!")
        while(port.inWaiting() == 0):
                time.sleep(0.5)
        port.write("X#")
        while(port.inWaiting() == 0):
                time.sleep(0.5)

        while(1):
                
                sys.stdout.write(port.read())
                #sys.stdout.write("\n")                

                
               
               

               
               

else:
    print("Port non ouvert")
