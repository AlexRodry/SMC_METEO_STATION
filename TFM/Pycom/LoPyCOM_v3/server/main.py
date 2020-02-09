from network import LoRa
import socket
import time

# Please pick the region that matches where you are using the device:
# Asia = LoRa.AS923
# Australia = LoRa.AU915
# Europe = LoRa.EU868
# United States = LoRa.US915

uart = UART(1, baudrate=115200)
lora = LoRa(mode=LoRa.LORA, region=LoRa.EU868)
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
s.setblocking(False)
print("Conexion establecida")
maxTimOut = 5   # Maximum iterations to the same ST
stations = ("ST01","ST02") # Stations to request
waitTime = 50

request = 0
nstations = len(stations)
timOut = 0
while True:
    try:
        s.send(stations[request])
        print(stations[request])

        time.sleep(0.5)
        loraread = s.recv(1024)

        msg = loraread.decode("utf-8")
        if len(loraread) > 5 and stations[request] in msg:
            stats = lora.stats()
            rssidB = str(stats.rssi)
            telegram = msg.replace("rssi", rssidB)
            uart.write(telegram)
            print(telegram)
            time.sleep(1.0)
            timOut = 0
            if request == nstations - 1:
                request = 0
            else:
                request = request + 1
            time.sleep(1.0)
        else:
            timOut = timOut + 1
            if timOut >= maxTimOut:
                timOut = 0
                if request == nstations - 1:
                    request = 0
                else:
                    request = request + 1
            time.sleep(10)

        time.sleep(waitTime)

    except Exception as e:
        print("Error ignorado en receptor")
