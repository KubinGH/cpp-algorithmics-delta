import glob

for filename in glob.glob("tests/*.*"):
    text = open(filename, "r").read().strip()
    text = text.replace("n", "\r\n")
    with open(filename, "w") as file:
        file.write(text)