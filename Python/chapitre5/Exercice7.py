import threading
import time
import random

mutex = threading.Lock()
u = 1.0
iter_count = 0

def t1():
    global u, iter_count
    while True:
        mutex.acquire()
        u = 0.25 * (u - 1.0) ** 2
        iter_count += 1
        val = u
        mutex.release()
        print("T1 u=", round(val, 4))
        time.sleep(random.randint(1, 5))

def t2():
    global u, iter_count
    while True:
        mutex.acquire()
        u = (1.0 / 6.0) * (u - 2.0) ** 2
        iter_count += 1
        val = u
        mutex.release()
        print("T2 u=", round(val, 4))
        time.sleep(random.randint(1, 5))

if __name__ == "__main__":
    th1 = threading.Thread(target=t1)
    th2 = threading.Thread(target=t2)
    th1.start()
    th2.start()
    th1.join()
    th2.join()