import os
import sys
import subprocess
import socket

def client():
    rep = sys.argv[1]
    subprocess.run(["tar", "czf", "/tmp/rep.tgz", rep])
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('127.0.0.1', 6666))
    with open("/tmp/rep.tgz", "rb") as f:
        while True:
            data = f.read(4096)
            if not 
                break
            sock.sendall(data)
    sock.close()
    os.remove("/tmp/rep.tgz")

if __name__ == "__main__":
    client()