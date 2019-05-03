import string

def b16encode(string, alphabet=string.hexdigits):
    result = ""
    for char in string:
        bn = bin(ord(char))[2:].zfill(8)
        result += "".join(alphabet[int(b, 2)]
                  for b in [bn[:4], bn[4:8]])
    return result
    
def b16decode(string, alphabet=string.hexdigits.upper()):
    result = ""
    fnd = alphabet.find
    for i in range(0, len(string), 2):
        b = (fnd(string[i])<<4) | fnd(string[i+1])
        if b != 0:
            result += chr(b) 
    return result

if __name__ == "__main__":
    s = 'int main() { cout << "Hello World"; }'
    print(b16encode(s))
    print(b16decode(b16encode(s)))