import re, glob
for filename in glob.glob("tests/*.in"):
    text = open(filename, "r", encoding="utf-8").read()
    if text.count("\n") != text.count("\r\n"):
        text = re.sub("\r(?!\n)|(?<!\r)\n", "\r\n", text)
    with open(filename, "w", encoding="utf-8") as file:
        file.write(text)