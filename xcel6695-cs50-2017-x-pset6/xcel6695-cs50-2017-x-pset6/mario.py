while True:
  try:
    a = int(input())
    if a >= 0:
      break
  except ValueError:
    print("", end = "")
i = 2
a = a + 1
val = a
while i <= a:
  tmp = val - i
  for j in range(0, tmp):
    print(" ", end = "")
  tmp = val - tmp
  for j in range(0, tmp):
    print("#", end = "")
  print("");
  i += 1