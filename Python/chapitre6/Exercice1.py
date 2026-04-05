print(f"a) {2*2*1000*60*1024}")
pos = (2*1000*60 + 350*60 + 45)*1024 + 300
print(f"b) {pos}")
o = 78000000
sec = o // 1024
print(f"c) secteur {sec%60}, cylindre {(sec//60)%1000}, face {(sec//60000)%2}")