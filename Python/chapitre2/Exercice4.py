import os

for i in range(1, 6):
    pid = os.fork()
    if pid == 0:
        print("Je suis le fils {i}")
        os._exit(0)
print("Je suis le père")

for _ in range(5):
    os.wait()
