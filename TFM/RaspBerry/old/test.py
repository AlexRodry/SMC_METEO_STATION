#!/usr/bin/env pyth.gg+on
import serial
import mysql.connector
import json

lora = serial.Serial('/dev/ttyUSB0', 115200)


while True:
	line = lora.readline()
	print(line)
lora.close() #Finalizamos la comunicacionarduino