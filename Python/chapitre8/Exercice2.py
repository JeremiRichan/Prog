import socket

def verifier_ip(ip_client):
    with open("add_autoris.txt") as f:
        for ligne in f:
            parts = ligne.split()
            if len(parts) == 2:
                ip_file = parts[0]
                nom_file = parts[1]
                if ip_file == ip_client:
                    return True, nom_file
    return False, ""

def main():
    serveur = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serveur.bind(('0.0.0.0', 9999))
    serveur.listen(5)
    conn, addr = serveur.accept()
    ip_client = addr[0]
    ok, nom = verifier_ip(ip_client)
    if ok:
        reponse = "Bienvenue {}\n".format(nom)
    else:
        reponse = "Refusé\n"
    conn.sendall(reponse.encode())
    conn.close()
    serveur.close()

if __name__ == "__main__":
    main()