import os
import random
import time

debut = time.time()
p1 = os.fork()

if p1 == 0:
    time.sleep(random.randint(1, 10))
    os._exit(0)
p2 = os.fork()
if p2 == 0:
    time.sleep(random.randint(1, 10))
    os._exit(0)
os.waitpid(p1, 0)
os.waitpid(p2, 0)
fin = time.time()

print("La durée total : {} secondes ".format(int(fin - debut)))