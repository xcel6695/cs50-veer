while True:
  print("O hai! How much change is owed?")
  try:
    change = float(input())
    if change >= 0.0:
      break
  except ValueError:
    print("", end = "")

number_of_coins = 0
cents = int(round(change * 100))
number_of_coins += cents // 25
cents %= 25
number_of_coins += cents // 10
cents %= 10
number_of_coins += cents // 5
cents %= 5
number_of_coins += cents
print("{}".format(number_of_coins))