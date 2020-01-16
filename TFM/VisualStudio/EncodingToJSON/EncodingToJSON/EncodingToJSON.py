import json
msg1 = "nombre|ST01|Fecha|20200112210808|1|41|2|91129|3|22.38|4|90|5|0.00|6|0.00|10|-69|"
msg2 = "nombre|ST02|Fecha|20200116181603|11|27|20|-121|"

def DcodetoJSON(Ecodemsg):
    """ Function to decode a msg into a vslid json, it is neccesary json library """
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

telegram1 = DcodetoJSON(msg1)
telegram2 = DcodetoJSON(msg2)
print(telegram1)
print(telegram2)

