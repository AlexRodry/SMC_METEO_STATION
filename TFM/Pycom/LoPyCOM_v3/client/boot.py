import os
import machine
import pycom
import time

# Configure first UART bus to see the communication on the pc
uart = machine.UART(0, 115200)
os.dupterm(uart)

# Configure second UART bus on pins P3(TX1) and P4(RX1)
uart1 = machine.UART(1, baudrate=115200, pins=('P11','P10'),timeout_char=5000)

pycom.heartbeat(False)

machine.main('main.py')
print('==========Starting main.py==========\n')
