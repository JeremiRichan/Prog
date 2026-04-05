import threading
import time
import random
import copy

mutex = threading.Lock()
tab = [0.0] * 100
for i in range(1, 99):
    tab[i] = random.uniform(0, 100)

def lisser():
    global tab
    while True:
        mutex.acquire()
        copie = copy.deepcopy(tab)
        for i in range(1, 99):
            copie[i] = (tab[i-1] + tab[i] + tab[i+1]) / 3.0
        tab = copie
        mutex.release()
        time.sleep(random.randint(1, 3))

def afficher():
    while True:
        mutex.acquire()
        for i in range(100):
            print(round(tab[i], 2), end=" ")
        print()
        mutex.release()
        time.sleep(4)

if __name__ == "__main__":
    t1 = threading.Thread(target=lisser)
    t2 = threading.Thread(target=afficher)
    t1.start()
    t2.start()
    t1.join()
    t2.join()