import os
import signal
import sys
def handler(s, f):
    print(f"Fils {os.getpid()} tué")
    os._exit(0)
fils = []
for i in range(5):
    p = os.fork()
    if p == 0:
        signal.signal(signal.SIGTERM, handler)
        while True:
            pass
    fils.append(p)
while True:
    line = sys.stdin.readline().split()
    if not line:
        break
    cmd = line[0]
    num = int(line[1])
    if cmd == 's':
        os.kill(fils[num], signal.SIGSTOP)
    elif cmd == 'r':
        os.kill(fils[num], signal.SIGCONT)
    elif cmd == 't':
        os.kill(fils[num], signal.SIGTERM)