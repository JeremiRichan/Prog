import threading
import random

def generer_tableau(resultat):
    tab = [0] * 10
    for i in range(10):
        tab[i] = random.randint(0, 99)
    resultat[0] = tab

if __name__ == "__main__":
    res = [None]
    th = threading.Thread(target=generer_tableau, args=(res,))
    th.start()
    th.join()
    print(res[0])