# main.py -- put your code here!

from network import LoRa
import socket
import time

lora = LoRa(mode = LoRa.LORA, region = LoRa.EU868)
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
s.setblocking(True)

while True:
	print('Waiting for LoRa data...')
	loraread = s.recv(256)
	if loraread != None:
		print('---> Sending over UART...')
		print(loraread)
	time.sleep(1)