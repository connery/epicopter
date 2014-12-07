#!/usr/bin/python-serial
#!/usr/bin/pyserial
#!/usr/sbin/update-python-modules

from serial import Serial
import time
import sys
import os

port = Serial('/dev/ttyACM0', 115200)
print(port.name)

if (port.isOpen() == 0):
	port.open()

if (port.isOpen()):
#	print("Port ouvert")
	time.sleep(2)
	
	port.write("!")
#	port.write("X#");
	
#	while(port.inWaiting() == 0):
#		time.sleep(0.5)

	

#	pid = os.fork()


	fd_read = os.fdopen((int)(sys.argv[1]), "r")
	# (PIPE UNIDIRECTIONNEL SERVEUR DRONE > COMMUNICATION.PY : LECTURE ) 

#	fd_write = os.fdopen((int)(sys.argv[2]), "w")
	# (PIPE UNIDIRECTIONNEL SERVEUR DRONE < COMMUNICATION.PY : ECRITURE ) 

#	if pid > 0:
		# enfant
				
#		while(1):
			
#			if (port.inWaiting() != 0):
			
#				buf_ = port.read()
#				sys.stdout.write(buf_)
			

#	else:
		#parent

	while(1):	
		buf = fd_read.read(2)
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

