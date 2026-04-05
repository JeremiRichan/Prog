n = int(input())
t = list(map(int, input().split()))
while True:
    try:
        i = int(input("Index: "))
        print(t[i])
        break
    except IndexError:
        print("Erreur")