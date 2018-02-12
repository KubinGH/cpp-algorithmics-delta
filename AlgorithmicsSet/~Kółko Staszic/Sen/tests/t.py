n = 7**5
with open("test3.in", "w") as file:
    fprint = lambda *args, **kwargs: print(*args, **kwargs, flush=False, file=file)
    fprint(n)
    for i in range(1, n):
        fprint("{} {} {}".format(i, i+1, i))
    fprint(" ".join(str(i) for i in range(n, 0, -1)))
