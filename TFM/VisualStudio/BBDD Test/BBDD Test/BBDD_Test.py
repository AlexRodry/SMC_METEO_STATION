#!/usr/bin/env pyth.gg+on

import mysql.connector
import json
from datetime import date
from datetime import datetime

lora = serial.Serial('/dev/ttyUSB0', 115200)


def cad_proc(cad):
    # try:

    j = json.loads(msg)
    st = j["nombre"]
    fecha = j["Dato"][0]["Fecha"]
    loctime = fecha
    samplefreq = "300"
    tipo = j["Dato"][1]["Tipo"]
    localizacion = "CAT URJC"
    if st == "ST01":
        humedad = j["sensores"][0]["valor"]
        presion = j["sensores"][1]["valor"]
        temperatura = j["sensores"][2]["valor"]
        dir_viento = j["sensores"][3]["valor"]
        vel_viento = j["sensores"][4]["valor"]
        pluvio = j["sensores"][5]["valor"]
        rssi = j["sensores"][6]["valor"]

        cnx = mysql.connector.connect(user='URJC_Estacion', password='SMC2019',
                            host='localhost',
                            database='WeatherStation')
        cursor = cnx.cursor()
        query = "Insert into `data` (`stime`, `loctime`, `localizacion_id`, `samplfreq`, `humedad`, `presion`, `temperatura`, `direccion_viento`, `velocidad_viento`, `lluvia`, `rssi`) VALUES (" + fecha  + "," + loctime + ","  + localizacion + "," + samplefreq  + "," + humedad  + "," + presion  + "," + temperatura  + "," + dir_viento + "," + vel_viento + "," + pluvio + "," + rssi + ");"
        print(query)
        cursor.execute(query)
        cnx.commit()
        cursor.close()
        cnx.close()
    elif st == "ST02":
        temperatura = j["sensores"][0]["valor"]
        rssi = j["sensores"][1]["valor"]
        cursor = cnx.cursor()
        query = "Insert into `data` (`stime`, `loctime`, `localizacion_id`, `temperatura`, `rssi`) VALUES (" + fecha  + "," + loctime + ","  + localizacion + "," + samplefreq  + temperatura  + ","  + rssi + ");"
        print(query)
        cursor.execute(query)
        cnx.commit()
        cursor.close()
        cnx.close()

    # except:  # includes simplejson.decoder.JSONDecodeError
    #   print('Esperando telegrama json...')

def DcodetoJSON(Ecodemsg):
	""" Function to decode a msg into a vslid json, it is neccesary json library """
	try:
		_SPLITCHARACTER = "|" 
		nBxs = 0

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
		print(Ecodemsg+" - Error in decoding process")

while True:
	line = lora.readline()
	print(line)
	msg = DcodetoJSON(line)
	cad_proc(msg)
lora.close() #Finalizamos la comunicacionarduino
