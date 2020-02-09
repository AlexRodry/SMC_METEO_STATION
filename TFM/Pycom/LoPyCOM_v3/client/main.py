from network import LoRa
import socket
import time

# Please pick the region that matches where you are using the device:
# Asia = LoRa.AS923
# Australia = LoRa.AU915
# Europe = LoRa.EU868
# United States = LoRa.US915

print('Main start')

lora = LoRa(mode=LoRa.LORA, region=LoRa.EU868)
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
s.setblocking(False)

# Waiting time
waitTime = 200
# station 01
handshake = "ST01"
# station 02
# handshake = "ST02"
readyToSend = False

while True:
	try:
		msg = uart1.readline()
		loraread = s.recv(1024)

		if msg != None:
			print(msg)

		if len(loraread) > 3:
			loraread = loraread.decode("utf-8")
			print(loraread)

		if loraread == handshake:
			readyToSend = True

		if msg != None and readyToSend == True:
			s.send(msg)
			print('msg enviado')
			print(msg)
			readyToSend = False
			time.sleep(waitTime)

	except Exception as e:
		s.send("Error en emisor Lora ignorado: "+handshake)
		print("Error en emisor Lora")
