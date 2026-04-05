import threading
import time
import random

plein = threading.Semaphore(0)
vide = threading.Semaphore(1)
buf = [0]

def emetteur():
    while True:
        octet = random.randint(0, 255)
        vide.acquire()
        buf[0] = octet
        plein.release()
        time.sleep(random.randint(1, 3))

def recepteur():
    while True:
        plein.acquire()
        val = buf[0]
        print("Lu:", val)
        vide.release()
        time.sleep(random.randint(1, 3))

if __name__ == "__main__":
    te = threading.Thread(target=emetteur)
    tr = threading.Thread(target=recepteur)
    te.start()
    tr.start()
    te.join()
    tr.join()