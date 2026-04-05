import os

p1 = os.fork()

if p1 == 0:
    print("Je suis le fils 1")
    os._exit(0)

p2 = os.fork()
if p2 == 0:
    print("Je suis le fils 2")
    os._exit(0)

os.waitpid(p1, 0)
os.waitpid(p2, 0)

print("Je suis le père")
