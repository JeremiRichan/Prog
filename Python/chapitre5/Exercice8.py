import threading
import time
import random

s1 = threading.Semaphore(0)
s2 = threading.Semaphore(1)

def rendez():
    for i in range(10):
        time.sleep(2)
        s2.acquire()
        print("Rendez-vous", i + 1)
        s1.release()

def autre():
    for i in range(10):
        temps = random.randint(4, 9)
        time.sleep(temps)
        s1.acquire()
        s2.release()

if __name__ == "__main__":
    t1 = threading.Thread(target=rendez)
    t2 = threading.Thread(target=autre)
    t1.start()
    t2.start()
    t1.join()
    t2.join()