# Librerías
from network import LoRa
import socket
import time
# Configuración de la frecuencia Lora:
# Asia = LoRa.AS923
# Australia = LoRa.AU915
# Europa = LoRa.EU868
# EEUU = LoRa.US915
print('Main start')
# Configuración del protocolo Lora
lora = LoRa(mode=LoRa.LORA, region=LoRa.EU868)
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
s.setblocking(False)

waitTime = 120			# Tiempo de espera
# handshake = "ST01"		# Handshake de llamada
handshake = "ST02"

while True:
	try:
		msg = uart1.readline()		# Lectura puerto serie
		loraread = s.recv(1024)		# Lectura Lora
# Comprobación del mensaje Arduino y almacenamiento en el buffer
		if msg != None:
			print(msg)
			if handshake in msg: # Comprobación mensaje correcto
				telegram = msg
# Handshake recibido por Lora
		if len(loraread) > 3:
			loraread = loraread.decode("utf-8")
			print(loraread)
# Activar envío si el handshake es el esperado
		if loraread == handshake:
# Envío datos mediante Lora
			s.send(telegram)
			print('msg enviado')
			print(telegram)
			time.sleep(waitTime)	# Modo bajo consumo
# Envío error al receptor si existiera
	except Exception as e:
		s.send("Error en emisor Lora ignorado: "+handshake)
		print("Error en emisor Lora")
