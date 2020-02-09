from datetime import date
from datetime import datetime
import time

inSt01 = datetime.now()
time.sleep(2.7)
finSt01 = datetime.now()
tSt01 = finSt01 - inSt01
samplefreq = tSt01.seconds
print(samplefreq)
