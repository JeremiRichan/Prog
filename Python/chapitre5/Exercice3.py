import threading
import random

class TypeTableau:
    def __init__(self, n, x):
        self.tab = [0] * n
        self.n = n
        self.x = x

def initialiser(obj):
    for i in range(obj.n):
        obj.tab[i] = random.randint(0, 99)

def chercher(obj, res):
    trouve = 0
    for i in range(obj.n):
        if obj.tab[i] == obj.x:
            trouve = 1
            break
    res[0] = trouve

if __name__ == "__main__":
    n = 5
    x = int(input("Entier x: "))
    obj = TypeTableau(n, x)
    res = [0]
    t1 = threading.Thread(target=initialiser, args=(obj,))
    t1.start()
    t1.join()
    t2 = threading.Thread(target=chercher, args=(obj, res))
    t2.start()
    t2.join()
    print(res[0])