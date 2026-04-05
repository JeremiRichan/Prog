import os
import signal
import sys
pid = os.fork()
if pid == 0:
    while True:
        pass
while True:
    k = sys.stdin.read(1)
    if k == 's':
        os.kill(pid, signal.SIGSTOP)
    elif k == 'r':
        os.kill(pid, signal.SIGCONT)
    elif k == 'q':
        os.kill(pid, signal.SIGTERM)
        break
os.wait()