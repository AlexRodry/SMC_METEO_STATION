#!/usr/bin/env pyth.gg+on
import serial
import mysql.connector
import json
from datetime import date
from datetime import datetime

lora = serial.Serial('/dev/ttyUSB0', 115200)

def formatDate(f):
    date = f[0:4]+'-'+f[4:6]+'-'+f[6:8]+' '+f[8:10]+':'+f[10:12]+':'+f[12:14]
    return date

def cad_proc(cad):
    try:
        print("JSON telegram: ")
        print(cad)
        j = json.loads(cad)
        st = j["nombre"]
        fecha = j["Dato"][0]["Fecha"]
        stdtime = formatDate(fecha)
        now = datetime.now()
        loctime = now.strftime('%Y-%m-%d %H:%M:%S')
        # samplefreq = "300"
        tipo = j["Dato"][1]["Tipo"]
        localizacion = "CAT URJC"
        cnx = mysql.connector.connect(user='URJC_Estacion', password='SMC2019',
                                host='localhost',
                                database='WeatherStation')
        if st == "ST01":
            finSt01 = datetime.now()
            tSt01 = finSt01 - inSt01
            samplefreq = tSt01.seconds
            inSt01 = datetime.now()
            humedad = j["sensores"][0]["valor"]
            presion = j["sensores"][1]["valor"]
            temperatura = j["sensores"][2]["valor"]
            dir_viento = j["sensores"][3]["valor"]
            vel_viento = j["sensores"][4]["valor"]
            pluvio = j["sensores"][5]["valor"]
            rssi = j["sensores"][6]["valor"]           
            cursor = cnx.cursor()
            query = "Insert into datos (station, stime, loctime, samplfreq, temperatura, humedad, presion, lluvia, direccion_viento, velocidad_viento,  rssi) VALUES (" +  "\'" + st + "\'" + "," + "\'"+ stdtime + "\'" + "," + "\'"+ loctime + "\'"+ "," + "\'"+ samplefreq  + "\'"+ "," + "\'"+ temperatura + "\'"+ "," + "\'"+ humedad + "\'"+ ","+ "\'"+ presion + "\'"+ ","+ "\'"+ pluvio + "\'"+ ","+ "\'"+ dir_viento + "\'"+ ","+ "\'"+ vel_viento+ "\'"+ ","+ "\'"+ rssi + "\'"+ ");"
            #INSERT INTO `datos` (`stime`, `loctime`, `samplfreq`, `temperatura`, `humedad`, `presion`, `lluvia`, `direccion_viento`, `velocidad_viento`, `rssi`) VALUES (NULL, '2020-01-15 00:00:00', '2020-01-16 00:00:00', '300', '27.5', '45', '96500', '0.00', '90', '0.00', '-57');
            print("Query to DataBase: ")
            print(query)
            cursor.execute(query)
            cnx.commit()
            cursor.close()
            cnx.close()
        elif st == "ST02":
            finSt02 = datetime.now()
            tSt02 = finSt02 - inSt02
            samplefreq = tSt02.seconds
            inSt02 = datetime.now()
            temperatura = j["sensores"][0]["valor"]
            rssi = j["sensores"][1]["valor"]
            cursor = cnx.cursor()
            query = "Insert into datos (station, stime, loctime, samplfreq, temperatura, rssi) VALUES (" +  "\'" + st + "\'" + "," + "\'"+ stdtime + "\'" + "," + "\'"+ loctime + "\'"+ "," + "\'"+ samplefreq  + "\'" + ","+ "\'"+ temperatura + "\'"+ ","+ "\'"+ rssi + "\'"+ ");"
            print("Query to DataBase: ")
            print(query)
            cursor.execute(query)
            cnx.commit()
            cursor.close()
            cnx.close()

    except(TypeError, ValueError, KeyError):
        print('JSON not parsed, there is an error in the telegram')
    except(mysql.connector.errors.ProgrammingError):
        print('Error in SQL Syntax')
    except(UnboundLocalError):
        if st == "ST01":
            print('Station 01 Frequency time error')
        else:
            print('Station 02 Frequency time error')


def DcodetoJSON(Ecodemsg):
    # Function to decode a msg into a vslid json, it is neccesary json library
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

inSt01 = datetime.now()
inSt02 = datetime.now()
print('SW Initialized at: ')
print(inSt01)

while True:
    line = lora.readline()
    print("Reading...")
    print(line)
    if len(line) > 7:
        print(line)
        msg = DcodetoJSON(line)
        cad_proc(msg)

lora.close()