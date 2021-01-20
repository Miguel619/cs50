change = float(0)
while (change <= 0):
    change = input("Change owned: ")
    try:
        change = float(change) * 100
    except ValueError:
        change = 0

coins = change / 25
coins = int(coins)
change -= coins * 25

coins += change / 10
coins = int(coins)
change -= int(change / 10) * 10

coins += change / 5
coins = int(coins)
change -= int(change / 5) * 5

coins += change / 1
coins = int(coins)
change -= int(change / 1) * 1

print(coins)
