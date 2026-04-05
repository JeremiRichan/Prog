import os
r, w = os.pipe()
pid = os.fork()
if pid == 0:
    os.close(r)
    mot = input("Mot: ")
    os.write(w, mot.encode() + b"\0")
    os._exit(0)
os.close(w)
mot = os.read(r, 256).decode().strip("\0")
with open("fichier.txt") as f:
    contenu = f.read().split()
trouve = 1 if mot in contenu else 0
print(trouve)
os.waitpid(pid, 0)