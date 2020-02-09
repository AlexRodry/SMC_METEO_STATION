# Librerías
from network import LoRa
import socket
import time
# Configuración primer puerto serie para conexión con la RaspBerry
uart = UART(1, baudrate=115200)
# Configuración de la frecuencia Lora:
# Asia = LoRa.AS923
# Australia = LoRa.AU915
# Europa = LoRa.EU868
# EEUU = LoRa.US915
lora = LoRa(mode=LoRa.LORA, region=LoRa.EU868)
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
s.setblocking(False)
print("Conexion establecida")

maxTimOut = 5               # Nº máximo de intentos para la misma estación
stations = ("ST01","ST02")  # Estaciones configuradas
waitTime = 50               # Tiempo de espera

request = 0                 # Inicialización índice del array de petición
nstations = len(stations)   # Número de estaciones
timOut = 0                  # Contador de iteraciones

while True:
    try:
        s.send(stations[request])   # Petición de envío a un emisor del array
        print(stations[request])

        time.sleep(0.5)
        loraread = s.recv(1024)     # Lectura del puerto Lora
# Decodificación del mensaje a utf-8
        msg = loraread.decode("utf-8")
# Filtro para detectar mensaje correcto
        if len(loraread) > 5 and stations[request] in msg:
            stats = lora.stats()        # Parámetros de la com. Lora
            print(stats)                # Muestra lso parámetros de la comunicación
            rssidB = str(stats.rssi)    # Obtención del rssi
            telegram = msg.replace("rssi", rssidB)  # Introducir rssi en el Telegrama
            uart.write(telegram)        # Mandar telegrama por puerto serie
            print(telegram)
            time.sleep(1.0)
            timOut = 0                  # Reinicio del contador de intentos
# Cambio del módulo a llamar
            if request == nstations - 1:
                request = 0
            else:
                request = request + 1
            time.sleep(1.0)
        else:                           # Aumento el contador de intentos
            timOut = timOut + 1
            if timOut >= maxTimOut:
                timOut = 0
                if request == nstations - 1:
                    request = 0
                else:
                    request = request + 1
            time.sleep(10)

        time.sleep(waitTime)            # Espera para la siguiente petición

    except Exception as e:              # Gestión de las excepciones
        print("Error ignorado en receptor")
