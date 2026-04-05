import threading
import random
import sys
import termios
import tty

def generer(n, tab, fini):
    for i in range(n):
        tab[i] = random.randint(0, 99)
    fini.set()

def verifier_inclusion(t1, t2, res, f1, f2, annule):
    f1.wait()
    f2.wait()
    if annule.is_set():
        return
    inclus = True
    for i in range(len(t1)):
        trouve = False
        for j in range(len(t2)):
            if t1[i] == t2[j]:
                trouve = True
                break
        if not trouve:
            inclus = False
            break
    res[0] = inclus

def ecouter_annulation(annule):
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        while True:
            char = sys.stdin.read(1)
            if char == "A":
                print("Annulation")
                annule.set()
                sys.exit(0)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

if __name__ == "__main__":
    n1 = 3
    n2 = 6
    t1 = [0] * n1
    t2 = [0] * n2
    f1 = threading.Event()
    f2 = threading.Event()
    res = [False]
    annule = threading.Event()
    t_g1 = threading.Thread(target=generer, args=(n1, t1, f1))
    t_g2 = threading.Thread(target=generer, args=(n2, t2, f2))
    t_v = threading.Thread(target=verifier_inclusion, args=(t1, t2, res, f1, f2, annule))
    t_a = threading.Thread(target=ecouter_annulation, args=(annule,))
    t_g1.start()
    t_g2.start()
    t_v.start()
    t_a.start()
    t_g1.join()
    t_g2.join()
    t_v.join()
    if not annule.is_set():
        print("Inclus:", res[0])