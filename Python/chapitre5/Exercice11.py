import threading
import time
import random

m_lect = threading.Lock()
m_ecrit = threading.Lock()
lecteurs = 0
db = [0] * 15

def lecteur():
    global lecteurs
    while True:
        m_lect.acquire()
        lecteurs += 1
        if lecteurs == 1:
            m_ecrit.acquire()
        m_lect.release()
        idx = random.randint(0, 14)
        print("Lit [", idx, "]=", db[idx])
        m_lect.acquire()
        lecteurs -= 1
        if lecteurs == 0:
            m_ecrit.release()
        m_lect.release()
        time.sleep(random.randint(1, 3))

def redacteur():
    while True:
        m_ecrit.acquire()
        idx = random.randint(0, 14)
        db[idx] = random.randint(0, 100)
        print("Ecrit [", idx, "]=", db[idx])
        m_ecrit.release()
        time.sleep(random.randint(1, 10))

if __name__ == "__main__":
    L = int(input("Nombre lecteurs: "))
    R = int(input("Nombre rédacteurs: "))
    threads = []
    for i in range(L):
        t = threading.Thread(target=lecteur)
        t.start()
        threads.append(t)
    for i in range(R):
        t = threading.Thread(target=redacteur)
        t.start()
        threads.append(t)
    for t in threads:
        t.join()