#!/usr/bin/env python
#
# Copyright (c) 2019, Pycom Limited.
#
# This software is licensed under the GNU GPL version 3 or any
# later version, with permitted additional terms. For more information
# see the Pycom Licence v1.0 document supplied with this file, or
# available at https://www.pycom.io/opensource/licensing
#

""" OTAA Node example compatible with the LoPy Nano Gateway """

from network import LoRa
import socket
import binascii
import struct
import time
import config

# initialize LoRa in LORAWAN mode.
# Please pick the region that matches where you are using the device:
# Asia = LoRa.AS923
# Australia = LoRa.AU915
# Europe = LoRa.EU868
# United States = LoRa.US915
lora = LoRa(mode=LoRa.LORAWAN, region=LoRa.EU868)

# create an OTA authentication params
# ST10
dev_eui = binascii.unhexlify('70B3D5499A92F798')
app_eui = binascii.unhexlify('70B3D57ED002893A')
app_key = binascii.unhexlify('BEA6330C19191085BAD4D26E34071F56')
# ST20
# dev_eui = binascii.unhexlify('70B3D5499A92F798')
# app_eui = binascii.unhexlify('70B3D57ED002893A')
# app_key = binascii.unhexlify('BEA6330C19191085BAD4D26E34071F56')

# set the 3 default channels to the same frequency (must be before sending the OTAA join request)
lora.add_channel(0, frequency=config.LORA_FREQUENCY, dr_min=0, dr_max=5)
lora.add_channel(1, frequency=config.LORA_FREQUENCY, dr_min=0, dr_max=5)
lora.add_channel(2, frequency=config.LORA_FREQUENCY, dr_min=0, dr_max=5)

# join a network using OTAA
lora.join(activation=LoRa.OTAA, auth=(dev_eui, app_eui, app_key), timeout=0, dr=config.LORA_NODE_DR)

# wait until the module has joined the network
while not lora.has_joined():
    time.sleep(2.5)
    print('Not joined yet...')

# remove all the non-default channels
for i in range(3, 16):
    lora.remove_channel(i)

# create a LoRa socket
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)

# set the LoRaWAN data rate
s.setsockopt(socket.SOL_LORA, socket.SO_DR, config.LORA_NODE_DR)

# make the socket non-blocking
s.setblocking(False)

time.sleep(5.0)

try:
	msg = uart1.readline()
	if msg != None:
		s.send("Patata")
		print('msg enviado')
		print(msg)
		time.sleep(1.0)
except Exception as e:
	s.send("Error en emisor Lora ignorado")

#for i in range (200):
#    pkt = b'PKT #' + bytes([i])
#    print('Sending:', pkt)
#    s.send(pkt)
#    time.sleep(4)
#    rx, port = s.recvfrom(256)
#    if rx:
#        print('Received: {}, on port: {}'.format(rx, port))
#    time.sleep(6)
