import os
import sys

n = int(sys.argv[1])
k = int(sys.argv[2])
fichier = f"/tmp/coef_{n}_{k}.txt"
if k == 0 or k == n:
    with open(fichier, "w") as f:
        f.write("1")
    sys.exit(0)
pid1 = os.fork()
if pid1 == 0:
    os.execv(sys.executable, [sys.executable, sys.argv[0], str(n - 1), str(k)])
pid2 = os.fork()
if pid2 == 0:
    os.execv(sys.executable, [sys.executable, sys.argv[0], str(n - 1), str(k - 1)])
os.waitpid(pid1, 0)
os.waitpid(pid2, 0)
f1 = f"/tmp/coef_{n-1}_{k}.txt"
f2 = f"/tmp/coef_{n-1}_{k-1}.txt"
with open(f1) as fp1:
    v1 = int(fp1.read().strip())
with open(f2) as fp2:
    v2 = int(fp2.read().strip())
with open(fichier, "w") as f:
    f.write(str(v1 + v2))