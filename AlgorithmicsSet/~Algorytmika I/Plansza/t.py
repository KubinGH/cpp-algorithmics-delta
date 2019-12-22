import os

while True:
    os.system("python gen.py > t.in")
    code = os.system("./b < t.in")
    print("!", code)
    if code:
        print(open("t.in").read().strip())
        break