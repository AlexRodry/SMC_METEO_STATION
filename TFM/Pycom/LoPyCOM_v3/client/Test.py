from network import LoRa
import socket
import time

# Please pick the region that matches where you are using the device:
# Asia = LoRa.AS923
# Australia = LoRa.AU915
# Europe = LoRa.EU868
# United States = LoRa.US915

print('Test start')

lora = LoRa(mode=LoRa.LORA, region=LoRa.EU868)
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
s.setblocking(False)

# station 01
handshake = "ST01"
# station 02
#handshake = "ST02"
readyToSend = False

while True:

	time.sleep(1.5)
	msg = uart1.readline()
	loraread = s.recv(1024)

	if msg != None:
		print(msg)

	if loraread != "b''":
		loraread = loraread.decode("utf-8")
		print(loraread)

	if loraread == handshake:
		readyToSend = True

	if msg != None and readyToSend == True:
		s.send(msg)
		print('msg enviado')
		print(msg)
		readyToSend = False
		time.sleep(5)
