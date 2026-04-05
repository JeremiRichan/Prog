import os
import struct
n = int(input())
t = list(map(int, input().split()))
with open("tab.bin", "wb") as f:
    for val in t:
        f.write(struct.pack("i", val))
os.chmod("tab.bin", 0o640)