import socket
import sys

def main():
    chemin = sys.argv[1]
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('127.0.0.1', 7777))
    with open(chemin, 'rb') as f:
        while True:
            data = f.read(1024)
            if not data:
                break
            sock.sendall(data)
    sock.close()

if __name__ == "__main__":
    main()