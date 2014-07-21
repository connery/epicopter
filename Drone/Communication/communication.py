#!/usr/bin/python-serial
#!/usr/bin/pyserial
#!/usr/sbin/update-python-modules

from serial import Serial
import time
import sys
import os

print("Connexion")
port = Serial('/dev/ttyACM0', 115200)
print(port.name)

if (port.isOpen() == 0):
	port.open()

if (port.isOpen()):
	print("Port ouvert")
	time.sleep(2)
	print("Debut de communication")
	port.write("!")
	
	while(port.inWaiting() == 0):
		time.sleep(0.5)


	

	pid = os.fork()

	if pid > 0:
		# enfant
		
		while(1):
			sys.stdout.write(port.read())

	else:
		#parent

		while(1):
			buf = sys.stdin.read(2)
#			sys.stdout.write(buf)
			port.write(buf)
#			port.write("X#")
	



			
			

	#port.write("s")

	#port.write("5123.45;1000;1000;1000;1100;")
	#time.sleep(3)
	#port.write("5123.45;1000;1000;1100;1000;")
	#time.sleep(3)
	#port.write("5123.45;1000;1100;1000;1000;")
	#time.sleep(3)
	#port.write("5123.45;1100;1000;1000;1000;")
	#time.sleep(3)
	#port.write("5123.45;1000;1000;1000;1000;")

	#while(port.inWaiting() == 0):
	#	time.sleep(0.5)

	print("Fin du programme")

else:
	print("Port non ouvert")

