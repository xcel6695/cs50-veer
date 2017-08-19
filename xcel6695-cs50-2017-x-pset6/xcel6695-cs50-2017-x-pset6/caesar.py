import cs50
import sys

def main():
  if len(sys.argv) != 2:
    print("Try again")
    exit(1)
  key = int(sys.argv[1])
  result = []
  print("Plaintext: ", end = "")
  message = cs50.get_string()
  for symbol in message:
    if symbol.isalpha():
      result.append(caesar(symbol, key))
    else:
      result.append(symbol)
  
  print("Ciphertext: ", end = "")              
  print("".join(result))
  exit(0)

def caesar(char, key):
  if char.isupper():
    return chr(((ord(char) - 65 + key) % 26) + 65)
  else:
    return chr(((ord(char) - 97 + key) % 26) + 97)
        
if __name__ == "__main__":
    main()
  
