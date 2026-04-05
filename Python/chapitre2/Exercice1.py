import os

pid = os.fork()

if pid == 0:
    print("Je suis le fils")
else:
    os.wait()
    print("Je suis le père")