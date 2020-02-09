import os
import machine
import pycom


# Configure first UART bus to see the communication on the pc
uart = machine.UART(0, 115200)
os.dupterm(uart)

# Configure second UART bus on pins P3(TX1) and P4(RX1)
#uart1 = machine.UART(1, baudrate=9600, pins=('P11','P10'), timeout_chars=5000)
uart1 = machine.UART(1, baudrate=9600, pins=('P11','P10'))

pycom.heartbeat(False)

machine.main('main.py')
print('==========Starting main.py==========\n')
