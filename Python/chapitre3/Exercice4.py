import os
import shutil

while True:
    rep = input("Repertoire (q pour quitter ) :")
    if rep == 'q' or rep == 'Q':
        break
    shutil.copytree(".", rep, dirs_exist_ok=True)