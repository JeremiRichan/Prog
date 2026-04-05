import os

fichier = input("Nom du fichier : ")

os.execv("/usr/bin/emacs", ["emacs", fichier])