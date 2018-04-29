from os import system
import test

KEEP = ["#import<iostream>\n", "#import<cstdio>\n", 
        "#define I (std::cin>>t?t:t)\n", "int "]

with open("liczba.cpp", "r") as file:
    s = file.read()
    r = ""
    i = 0
    while i < len(s):
        for k in KEEP:
            if s[i:i+len(k)] == k:
                r += k
                i += len(k)
                break
        else:
            if not s[i].isspace():
                r += s[i]
            i += 1
    print(r)
with open("liczba-min.cpp", "w") as file:
    file.write(r)

print("= Compiling =")
compile_ok = 0 == system("g++ -O2 -pedantic -Wextra -Wall -std=c++98 -c liczba-min.cpp -o liczba-min.o")
if compile_ok: 
    compile_ok = 0 == system("g++ -O2 -pedantic -Wextra -Wall -std=c++98 -o liczba-min.exe liczba-min.o")
if compile_ok:
    print("= Testing =")
    test_ok = test.main("liczba-min.exe", False)
else:
    test_ok = None
if compile_ok and test_ok:
    print("Success!")
    print(f"Length: {len(r)}")
else:
    print("Failure.")
    print(f"Compilation OK: {compile_ok}\nTests OK: {test_ok}")
system("pause")