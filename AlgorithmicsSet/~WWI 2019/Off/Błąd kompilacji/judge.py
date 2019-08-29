import sys
import re

filename = sys.argv[1]

with open(filename, "r") as file:
    text = file.read(100 * 1024)

f = re.findall("[0-9]+", text)

print(len(set(f)))
