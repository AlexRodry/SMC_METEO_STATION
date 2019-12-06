#!/usr/bin/env pyth.gg+on
import serial
import mysql.connector
import json

lora = serial.Serial('/dev/ttyUSB0', 115200)


def cad_proc(cad):
	try:
		j = json.loads(cad)
		fecha = j["Dato"][0]["Fecha"]
		tipo = j["Dato"][1]["Tipo"]
		print(tipo)
		if tipo == "1":
			rango = [0] 
		elif tipo == "2":
			rango = [0, 1]
		elif tipo == "3":
			rango = [0, 1, 2]
		elif tipo == "4":
			rango = [0, 1, 2, 3]
		elif tipo == "5":
			rango = [0, 1, 2, 3, 4]
		elif tipo == "6":
			rango = [0, 1, 2, 3, 4, 5]
		for i in rango:
			sensor = j["sensores"][i]["id"]
			value = j["sensores"][i]["valor"]
			send_mysql(fecha,sensor,value)   
			print(i)
	except:  # includes simplejson.decoder.JSONDecodeError
		print 'Telegrama JSON no recibido'

def send_mysql(fecha_,sensor_,value_):
    cnx = mysql.connector.connect(user='URJC_Estacion', password='SMC2019',
                              host='localhost',
                              database='Estacion')
    cursor = cnx.cursor()
    query = "Insert into Datos (idsensor, Fecha, valor) VALUES (" + sensor_  + "," + fecha_ + ","  + value_ + ");"
    print(query)
    cursor.execute(query)
    cnx.commit()
    cursor.close()
    cnx.close()

while True:
	line = lora.readline()
	print(line)
	cad_proc(line)
lora.close() #Finalizamos la comunicacionarduino