N = 10**6
S = (N//4)*"A" + (N//4)*"C" + (N//4)*"G" + (N//4)*"T"
with open("tests-own/testz.in", "w") as f:
    f.write(S + "\n" + S)