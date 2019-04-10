#!/usr/bin/env pyth.gg+on
import serial
import mysql.connector
import json

arduino = serial.Serial('/dev/ttyUSB0', 9600)


def cad_proc(cad):
	print (cad)
	#json.load
	j = json.loads(cad)
	dia = j["Fecha"][0]["Dia"]
	print (dia)
	hora = j["Fecha"][1]["Hora"]
	print (hora)
	tipo = j["Fecha"][2]["Tipo"]
	print (tipo)
	if tipo == "1":
		rango = [0] 
	elif tipo == "2":
		rango = [0, 1]
	else:
		rango = [0, 1, 2]
	for i in rango:
		sensor = j["sensores"][i]["id"]
		print (sensor)
		value = j["sensores"][i]["valor"]
		print (value)
		send_mysql(dia,hora,sensor,value)   

def send_mysql(dia_,hora_,sensor_,value_):
    cnx = mysql.connector.connect(user='URJC_Estacion', password='SMC2019',
                              host='localhost',
                              database='Estacion')
    cursor = cnx.cursor()
    query = "Insert into Datos (idsensor, Dia, Hora, valor) VALUES (" + sensor_  + "," + dia_ + "," + hora_ + ","  + value_ + ");"
    print(query)
    cursor.execute(query)
    cnx.commit()
    cursor.close()
    cnx.close()

while True:
	line = arduino.readline()
	print (line)
	cad_proc(line)
arduino.close() #Finalizamos la comunicacionarduino = serial.Serial('/dev/ttyACM0', 9600)