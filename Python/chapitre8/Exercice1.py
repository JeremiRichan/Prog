import socket
import time

def charger_base():
    base = {}
    with open("base.txt") as f:
        for ligne in f:
            parts = ligne.split()
            if len(parts) == 2:
                base[parts[0]] = float(parts[1])
    return base

def gerer_client(conn, base):
    total = 0
    while True:
        data = conn.recv(256).decode().strip()
        if not 
            break
        parts = data.split()
        if len(parts) >= 2:
            prod = parts[0]
            qty = int(parts[1])
            if prod in base:
                total += base[prod] * qty
    reponse = "Total: {:.2f}\n".format(total)
    conn.sendall(reponse.encode())
    timestamp = time.strftime("%Y%m%d_%H%M%S")
    nom_fichier = "cmd_{}.txt".format(timestamp)
    with open(nom_fichier, "w") as f:
        f.write("Commande\n")
        f.write("Total: {:.2f}\n".format(total))
    conn.close()

def main():
    base = charger_base()
    serveur = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serveur.bind(('0.0.0.0', 8888))
    serveur.listen(5)
    while True:
        conn, addr = serveur.accept()
        gerer_client(conn, base)

if __name__ == "__main__":
    main()