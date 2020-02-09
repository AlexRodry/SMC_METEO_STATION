# Librerías
import os
import machine
import pycom

# Configuración primer puerto serie para conexión con el PC
uart = machine.UART(0, 115200)
os.dupterm(uart)
# Configuración segundo puerto serie para conexión con Arduino
# Se empleará P11 como TX y P10 como RX
uart1 = machine.UART(1, baudrate=9600, pins=('P11','P10'))
# Desactivación del Led para reducir el consumo
pycom.heartbeat(False)
# Configuración del programa principal
machine.main('main.py')
print('==========Starting main.py==========\n')
