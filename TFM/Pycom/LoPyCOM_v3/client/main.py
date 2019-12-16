from network import LoRa
from machine import Pin
import socket
import time
import sys

# Please pick the region that matches where you are using the device:
# Asia = LoRa.AS923
# Australia = LoRa.AU915
# Australia = LoRa.AU915
# Europe = LoRa.EU868
# United States = LoRa.US915

print('Main start')

HSoutput = Pin('P9', mode=Pin.OUT, pull=None)
HSinput = Pin('P13', mode=Pin.IN, pull=None)
hsControl =	1;

lora = LoRa(mode=LoRa.LORA, region=LoRa.EU868)
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
s.setblocking(False)

print('Running')

while True:
	try:
		if hsControl == 1:
			HSoutput(0)
			if (HSinput() == True):
				msg = uart1.readline()
				if (HSinput() == False and msg != None):
					print(msg)
					hsControl = 2
		if hsControl == 2:
			HSoutput(1)
			s.send(msg)
			if (HSinput() == False):
				hsControl = 1
				print("Sleeping")
				time.sleep(5)
	except Exception as e:
		s.send("Error en emisor Lora ignorado")
