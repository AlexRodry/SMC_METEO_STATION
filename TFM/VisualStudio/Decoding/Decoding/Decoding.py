import json
msg = "nombre|ST01|Fecha|20200112210808|1|41|2|91129|3|22.38|4|90|5|0.00|6|0.00|10|-69|"

_SPLITCHARACTER = "|" 
nBoxes = 0
decodeTelegram = []

for letter in msg:
    if(letter == _SPLITCHARACTER):
        nBoxes += 1
nIds = str((nBoxes - 4)/2)

decodeArray = msg.split(_SPLITCHARACTER)
del decodeArray[nBoxes]

datoArray = []
sensoresArray = []

sensors = {}
for i in range(nIds):
    sensors{id}

for i in range(4,nBoxes, 2):
	tempsens[decodeArray[i]] = decodeArray[i+1]
    sensoresArray.insert = (i-4, sensors{})

jsonEncode = {}
jsonEncode[decodeArray[0]] = decodeArray[1]
jsonEncode["Dato"] = datoArray
jsonEncode["sensores"] = sensoresArray



jsonTelegram = json.dumps(jsonEncode)
print(jsonTelegram)
