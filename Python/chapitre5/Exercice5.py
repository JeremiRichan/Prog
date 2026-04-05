import threading
import time
import random
import sys

mutex = threading.Lock()
compt = 0
limite = int(sys.argv[1])

def incrementer():
    global compt
    while True:
        mutex.acquire()
        compt += 1
        fin = compt >= limite
        mutex.release()
        if fin:
            break
        time.sleep(random.randint(1, 5))

def afficher():
    while True:
        mutex.acquire()
        val = compt
        fin = compt >= limite
        mutex.release()
        if fin:
            break
        print(val)
        time.sleep(2)

if __name__ == "__main__":
    t1 = threading.Thread(target=incrementer)
    t2 = threading.Thread(target=afficher)
    t1.start()
    t2.start()
    t1.join()
    t2.join()