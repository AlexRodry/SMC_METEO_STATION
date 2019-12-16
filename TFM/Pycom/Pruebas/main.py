from network import LoRa
from machine import Pin
import socket
import time

# Please pick the region that matches where you are using the device:
# Asia = LoRa.AS923
# Australia = LoRa.AU915
# Europe = LoRa.EU868
# United States = LoRa.US915

print('Main start')

HSoutput = Pin('P9', mode=Pin.OUT, pull=None)
HSinput = Pin('P8', mode=Pin.IN, pull=None)
hsControl =	1;

while True:
		time.sleep(3)
		if hsControl == 1:
			print("Caso 1.1")
			HSoutput.value(1)
			msg = uart1.readline()
			if (msg != None and HSinput.value() == True):
				print("Caso 1.2")
				print(msg)
				hsControl = 2
		if hsControl == 2:
			print("Caso 2.1")
			HSoutput.value(0)
			if HSinput.value() == 0:
				print("Caso 2.2")
				hsControl = 1
				time.sleep(5)
