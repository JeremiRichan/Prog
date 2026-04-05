import threading
import time
import random

TAILLE = 10
buffer = [0] * TAILLE
en_tete = 0
queue = 0
mutex = threading.Lock()
vide = threading.Semaphore(TAILLE)
plein = threading.Semaphore(0)

def producteur():
    global en_tete
    while True:
        item = random.randint(0, 255)
        vide.acquire()
        mutex.acquire()
        buffer[en_tete] = item
        en_tete = (en_tete + 1) % TAILLE
        mutex.release()
        plein.release()
        time.sleep(random.randint(1, 3))

def consommateur():
    global queue
    while True:
        plein.acquire()
        mutex.acquire()
        item = buffer[queue]
        queue = (queue + 1) % TAILLE
        mutex.release()
        print("Consommé:", item)
        vide.release()
        time.sleep(random.randint(1, 3))

if __name__ == "__main__":
    N = int(input("Nombre producteurs: "))
    M = int(input("Nombre consommateurs: "))
    prod_threads = []
    cons_threads = []
    for i in range(N):
        t = threading.Thread(target=producteur)
        t.start()
        prod_threads.append(t)
    for i in range(M):
        t = threading.Thread(target=consommateur)
        t.start()
        cons_threads.append(t)
    for t in prod_threads:
        t.join()
    for t in cons_threads:
        t.join()