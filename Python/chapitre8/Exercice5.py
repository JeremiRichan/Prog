import socket
import threading

def relais(src, dst):
    while True:
        data = src.recv(256)
        if not 
            break
        msg = data.decode().strip()
        reponse = "L'autre client dit: {}\n".format(msg)
        dst.sendall(reponse.encode())

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('0.0.0.0', 5555))
    sock.listen(2)
    c1, _ = sock.accept()
    c2, _ = sock.accept()
    t1 = threading.Thread(target=relais, args=(c1, c2))
    t2 = threading.Thread(target=relais, args=(c2, c1))
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    c1.close()
    c2.close()
    sock.close()

if __name__ == "__main__":
    main()