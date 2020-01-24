import json
from datetime import date
from datetime import datetime

# msg = "{\"nombre\":\"ST01\",\"Dato\":[{\"Fecha\":\"202001115065100\"},{\"Tipo\":\"1\"}],\"sensores\":[{\"id\":\"1\",\"valor\":\"45\"},{\"id\":\"2\",\"valor\":\"9991\"},{\"id\":\"3\",\"valor\":\"24,5\"},{\"id\":\"4\",\"valor\":\"270\"},{\"id\":\"5\",\"valor\":\"7.1\"},{\"id\":\"6\",\"valor\":\"12.1\"},{\"id\":\"10\",\"valor\":\"-69\"}]}"
msg = "{\"nombre\":\"ST02\",\"Dato\":[{\"Fecha\":\"202001115065100\"},{\"Tipo\":\"1\"}],\"sensores\":[{\"id\":\"11\",\"valor\":\"25.9\"},{\"id\":\"20\",\"valor\":\"-69\"}]}"
print(msg)

#try:

j = json.loads(msg)
st = j["nombre"]
fecha = j["Dato"][0]["Fecha"]
loctime = str(datetime.now())
samplefreq = "300"
tipo = j["Dato"][1]["Tipo"]
localizacion = "CAT URJC"
if st == "ST01":
    humedad = sensor = j["sensores"][0]["valor"]
    presion = sensor = j["sensores"][1]["valor"]
    temperatura = sensor = j["sensores"][2]["valor"]
    dir_viento = sensor = j["sensores"][3]["valor"]
    vel_viento = sensor = j["sensores"][4]["valor"]
    pluvio = sensor = j["sensores"][5]["valor"]
    rssi = sensor = j["sensores"][6]["valor"]
    print("humedad: "+humedad," presión :"+presion," temperatura :"+temperatura," dir viento :"+dir_viento," vel viento :"+vel_viento," lluvia :"+pluvio," rssi :"+rssi)
    #cnx = mysql.connector.connect(user='URJC_Estacion', password='SMC2019',
    #                   host='localhost',
    #                   database='WeatherStation')
    #cursor = cnx.cursor()
    query = "Insert into data (stime, loctime, localizacion_id, samplfreq, humedad, presion, temperatura, direccion_viento, velocidad_viento, lluvia, rssi) VALUES (" + fecha  + "," + loctime + ","  + localizacion + "," + samplefreq  + "," + humedad  + "," + presion  + "," + temperatura  + "," + dir_viento + "," + vel_viento + "," + pluvio + "," + rssi + ");"
    print(query)
    #cursor.execute(query)
    #cnx.commit()
    #cursor.close()
    #cnx.close()
elif st == "ST02":
    temperatura = sensor = j["sensores"][0]["valor"]
    rssi = sensor = j["sensores"][1]["valor"]
    print("temperatura :"+temperatura)
    #cursor = cnx.cursor()
    query = "Insert into Datos (stime, loctime, localizacion_id, temperatura, rssi) VALUES (" + fecha  + "," + loctime + ","  + localizacion + "," + samplefreq  + temperatura  + ","  + rssi + ");"
    print(query)
    #cursor.execute(query)
    #cnx.commit()
    #cursor.close()
    #cnx.close()

#except:  # includes simplejson.decoder.JSONDecodeError
	#print('Esperando telegrama json...')