import os, sys
desc = int(sys.argv[1])
print(os.read(desc, 256).decode().strip())