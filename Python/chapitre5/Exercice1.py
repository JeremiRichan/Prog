 import threading

def afficher_tableau(tab):
    for i in range(len(tab)):
        print(tab[i])

if __name__ == "__main__":
    tableau = [10, 20, 30, 40, 50]
    th = threading.Thread(target=afficher_tableau, args=(tableau,))
    th.start()
    th.join()