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


while True:
    loraread = s.recv(256)
    msg = loraread.decode("utf-8")
    if loraread != None:
        uart.write(msg)
        print(msg)
    time.sleep(5)
