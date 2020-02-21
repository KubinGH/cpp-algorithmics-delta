from pistestgen import gen

def get_words(text):
    words = [w.strip(".,?!:;'\"()[]-") for w in text.lower().split()]
    words = [w for w in words if w]
    return words

def overlay(S, Z):
    for k in reversed(range(min(len(S), len(Z))+1)):
        for i in range(k):
            if i+(len(S)-k) < len(S) and i < len(Z) and S[i+(len(S)-k)] != Z[i]:
                break
        else:
            return k

K = 8
x, y = gen(4, 1000)

W = [get_words(t) for t in x]
print([len(w) for w in W], "->", len(W))

for tr in range(1):
    VV = []

    while W:
        u = W[-1]
        print(f"merging <{len(u)}words>")
        for v in W[:-1]:
            for _ in range(2):
                k = overlay(u, v)
                if u in v:
                    if u in W: W.remove(u)
                    break
                if k >= K:
                    if u in W: W.remove(u)
                    if v in W: W.remove(v)
                    W.append(u + v)
                    break
                u, v = v, u
            else:
                continue
            # jeżeli był merge to wychodzimy
            break
        # jeżeli nie było merge to dodajemy do końcowych
        else:
            print(f"done <{len(u)}words>")
            W.remove(u)
            VV.append(u)

    print([len(w) for w in VV], "->", len(VV))
    W = VV
