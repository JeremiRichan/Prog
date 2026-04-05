import os
r, w = os.pipe()
pid = os.fork()
if pid == 0:
    os.dup2(r, 0)
    os.close(r)
    os.close(w)
    mot = input()
    print("Lu:", mot)
    os._exit(0)
os.close(r)
with open("fichier.txt") as f:
    os.write(w, f.read().encode())
os.close(w)
os.waitpid(pid, 0)