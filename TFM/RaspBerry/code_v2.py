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
		elif tipo == "7":
			rango = [0, 1, 2, 3, 4, 5, 6]
		elif tipo == "8":
			rango = [0, 1, 2, 3, 4, 5, 6, 7]
		elif tipo == "9":
			rango = [0, 1, 2, 3, 4, 5, 6, 7, 8]
		elif tipo == "10":
			rango = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
		for i in rango:
			sensor = j["sensores"][i]["id"]
			value = j["sensores"][i]["valor"]
			send_mysql(fecha,sensor,value)   
	except:  # includes simplejson.decoder.JSONDecodeError
		print 'Esperando telegrama json...'

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

def DcodetoJSON(Ecodemsg):
	""" Function to decode a msg into a vslid json, it is neccesary json library """
	try:
		_SPLITCHARACTER = "|" 
		nBxs = 0
		decodeTelegram = []

		for letter in Ecodemsg:
			if(letter == _SPLITCHARACTER):
				nBxs += 1
		nIds = str(int((nBxs - 4)/2))

		dAr = Ecodemsg.split(_SPLITCHARACTER)
		del dAr[nBxs]

		jsonHead = json.dumps(dAr[0])+":"+json.dumps(dAr[1])

		jsonDato = json.dumps("Dato")+":"+"[{"+json.dumps(dAr[2])+":"+json.dumps(dAr[3])+"},{"+json.dumps("Tipo")+":"+json.dumps(nIds)+"}]"

		jsonSens=json.dumps("sensores")+":["
		for i in range(4,nBxs,2):
			jsonSens = jsonSens+"{"+json.dumps("id")+":"+json.dumps(dAr[i])+","+json.dumps("valor")+":"+json.dumps(dAr[i+1])+"}"
			if i < nBxs-2:
				jsonSens = jsonSens + ","
			else:
				jsonSens = jsonSens + "]"

		jsonTelegram = "{"+jsonHead+","+jsonDato+","+jsonSens+"}"
		return jsonTelegram
	except:  # includes simplejson.decoder.JSONDecodeError
		print(Ecodemsg)

while True:
	line = lora.readline()
	print(line)
	msg = DcodetoJSON(line)
	cad_proc(msg)
lora.close() #Finalizamos la comunicacionarduino