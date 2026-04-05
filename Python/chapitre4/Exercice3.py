import os
r, w = os.pipe()
pid = os.fork()
if pid == 0:
    os.close(r)
    os.execv("./fils.py", ["./fils.py", str(w)])
os.close(w)
os.write(r, b"message\n")
os.close(r)
os.waitpid(pid, 0)