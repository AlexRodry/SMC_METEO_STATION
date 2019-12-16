from network import LoRa
import socket
import time
from machine import Pin

# Please pick the region that matches where you are using the device:
# Asia = LoRa.AS923
# Australia = LoRa.AU915
# Europe = LoRa.EU868
# United States = LoRa.US915

hsin = Pin('P13', mode=Pin.IN)
hsout = Pin('P9', mode=Pin.OUT)

print('Main start 2')

lora = LoRa(mode=LoRa.LORA, region=LoRa.EU868)
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
s.setblocking(False)

while True:
	try:
		if hsin() == 1:
			hsout.value(1)
			msg = uart1.readline()
			if msg != None:
				s.send(msg)
				print('msg enviado')
				print(msg)
				time.sleep(5)
				hsout.value(0)
	except Exception as e:
		s.send("Error en emisor Lora ignorado")
