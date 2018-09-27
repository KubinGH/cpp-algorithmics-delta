import sys, os

for (n, f) in [(7, "output006.txt"), (64, "output007.txt"), 
               (110, "output008.txt"), (124, "output009.txt")]:
    if "gen_maxsub" in sys.modules:
        del sys.modules["gen_maxsub"]
    import gen_maxsub
    print(n, f)
    gen_maxsub.n = n
    gen_maxsub.FILE = open(f, "w")
    gen_maxsub.silent = True
    gen_maxsub.main()
    print("===\n")
    gen_maxsub.FILE.close()
