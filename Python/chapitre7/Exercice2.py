import os
import signal
import time
import sys
pid = os.fork()
if pid == 0:
    n = input("Entier: ")
    with open("/tmp/entier.txt", "w") as f:
        f.write(n)
    os.kill(os.getppid(), signal.SIGUSR1)
    os._exit(0)
def handler(s, frame):
    with open("/tmp/entier.txt") as f:
        print(f"Lu: {f.read().strip()}")
signal.signal(signal.SIGUSR1, handler)
signal.pause()
os.wait()