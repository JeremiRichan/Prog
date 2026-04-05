import socket
import threading

mutex = threading.Lock()
clients = []

def gerer_client(conn):
    while True:
        data = conn.recv(256)
        if not 
            break
        msg = data.decode()
        with mutex:
            for c in clients:
                if c != conn:
                    c.sendall(msg.encode())
    conn.close()
    with mutex:
        clients.remove(conn)

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('0.0.0.0', 4444))
    sock.listen(10)
    while True:
        conn, addr = sock.accept()
        with mutex:
            clients.append(conn)
        t = threading.Thread(target=gerer_client, args=(conn,))
        t.start()

if __name__ == "__main__":
    main()