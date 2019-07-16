import glob
with open("cfg.yml", "w", encoding="utf-8") as f:
    fprint = lambda *args, **kwargs: print(*args, **kwargs, file=f)
    fprint("""
title:
    Płytkafelki
points:
    1: 5
    2: 20
    3: 15
    4: 25
    5: 35
""".strip())
    X = []
    for x in glob.glob(r"in\*.in"):
        x = x[:-3]
        x = x[x.find("\\")+1:]
        X.append(x)
    fprint("memory_limits:")
    for x in X:
        fprint(f"    {x}: 65536")
    fprint("time_limits:")
    for x in X:
        fprint(f"    {x}: 500")
