import os

fichier = []
while True:
    f = input("Fichier (q pour quitter ) :")
    if f == 'q' or f == 'Q':
        break
    fichier.append(f)

if fichier:
    os.execv("emacs", ["emacs"])