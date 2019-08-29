import re

patterns = {
    "32": "(1<<(1+1+1+1+1))"
}

with open("choinka.c", "r") as f:
    code = f.read()

for a, b in patterns.items():
    code = re.sub(a, b)

with open("choinka1.c", "w") as f:
    f.write(code)
