#!/usr/bin/env pyth.gg+on
import serial
import mysql.connector
import json

arduino = serial.Serial('/dev/ttyUSB0', 9600)


def cad_proc(cad):
	j = json.loads(cad)
	fecha = j["Dato"][0]["Fecha"]
	tipo = j["Dato"][1]["Tipo"]
	if tipo == "1":
		rango = [0] 
	elif tipo == "2":
		rango = [0, 1]
	else:
		rango = [0, 1, 2]
	for i in rango:
		sensor = j["sensores"][i]["id"]
		value = j["sensores"][i]["valor"]
		send_mysql(fecha,sensor,value)   

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
	line = arduino.readline()
	cad_proc(line)
arduino.close() #Finalizamos la comunicacionarduino