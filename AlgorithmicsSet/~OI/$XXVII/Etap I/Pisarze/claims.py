import random
import string
from collections import Counter, defaultdict

import tqdm

COMMON = 6000

names = ["Mickiewicz", "Prus", "Sienkiewicz"]
texts = [open(f"{name}.txt", "r").read() for name in names]
words = [[w.strip(".,?!:;'\"()[]-") for w in text.lower().split()] for text in texts]
words = [[w for w in W if w] for W in words]
quant = [len(W) for W in words]

def get_words(text):
    words = [w.strip(".,?!:;'\"()[]-") for w in text.lower().split()]
    words = [w for w in words if w]
    words.extend([c for c in text if c in ".,?!:;'\"()[]-"])
    return words

D = {}
counters = [Counter(W) for W in words]

for i in range(3):
    for w, c in counters[i].most_common(COMMON):
        D[w] = tuple([counters[i][w] / quant[i] for i in range(3)])

def group_prefixwise(occstrings):
    DD = []
    I = sorted(occstrings)
    i = 0
    while i < len(I):
        j = i+1
        while j < len(I) and (len(I[i][0]) > 2 and I[j][0].startswith(I[i][0][:-1]) and len(I[i][0])/len(I[j][0]) >= 0.55):
            I[i] = (I[i][0], tuple(x+y for x, y in zip(I[i][1], I[j][1])))
            print("merge", I[j][0], "to", I[i][0])
            j += 1
        DD.append(I[i])
        i = j
    return DD

DD = sorted(D.items())
#DD = group_prefixwise(D.items())
DDD = dict(DD)
for k, v in DD:
    print(f"{k}: {[round(w, 3) if w > 1e-6 else None for w in v]}")

R = [sum(v[i] for k, v in DD) for i in range(3)]
print(R)

print([d[0] for d in DD])
print(len(DD))
print(sum(len(d[0]) for d in DD))

very_strong_claim = [[], [], []]
strong_claim = [[], [], []]
weak_claim = [[], [], []]
very_weak_claim = [[], [], []]

for k, v in DD:
    for i in range(3):
        other = [j for j in range(3) if i != j]
        if max(v[j] for j in other) < 1e-8:
            very_strong_claim[i].append(k)
        elif v[i] > sum(v[j] for j in other):
            strong_claim[i].append(k)
        elif v[i] == max(v[j] for j in range(3)):
            weak_claim[i].append(k)
        elif v[i] > min(v[j] for j in range(3)):
            very_weak_claim[i].append(k)

print("===\nvery strong\n===")
for i in range(3):
    print("--\n", names[i], very_strong_claim[i])
print("===\nstrong\n===")
for i in range(3):
    print("--\n", names[i], strong_claim[i])
print("===\nweak\n===")
for i in range(3):
    print("--\n", names[i], weak_claim[i])
print("===\nvery weak\n===")
for i in range(3):
    print("--\n", names[i], very_weak_claim[i])

claims = [[], [], []]
for i in range(3):
    claims[i] = [very_weak_claim[i], weak_claim[i], strong_claim[i], very_strong_claim[i]]
    for c in claims[i]:
        p = 0
        for k in c:
            p += DDD[k][i]
        print(f"{p*100:.2f}%", end="; ")
    print()


special = (
    (0, 2, '"'), (0, 2, ';'), (1, 2, "'"), (1, 2, '-'),
    (1, 2, '.'), (0, 1, '!'), (1, 1, '?'), (2, 1, ','),
    (0, 0, ','), (0, 0, '?'), (1, 0, '!'), (1, 0, '"'),
    (1, 0, ';'), (2, 0, "'"), (2, 0, '-'), (2, 0, '.')
)
for i, k, w in special:
    claims[i][k].append(w)


b64 = string.digits + string.ascii_uppercase + string.ascii_lowercase + '+/'
def b64_collapse(arr, bits):
    assert 6 % bits == 0
    print(len(arr), bits)
    assert len(arr) % (6//bits) == 0
    bi = "".join(bin(x)[2:].zfill(bits) for x in arr)
    result = "".join(b64[int(bi[i:i+6], 2)] for i in range(0, len(bi), 6))
    assert b64_expand(result, bits) == arr
    return result
def b64_expand(string, bits):
    assert 6 % bits == 0
    bi = "".join(bin(b64.find(b))[2:].zfill(6) for b in string)
    return [int(bi[i:i+bits], 2) for i in range(0, len(bi), bits)]


def string_run_compress(strings):
    curr = ""
    out = ""
    for string in strings:
        assert string.isalpha() and string.lower() == string
        d = 0
        while not string.startswith(curr):
            curr = curr[:-1]
            d += 1
        assert d <= 32
        out += b64[d]
        for i in range(len(curr), len(string)):
            curr += string[i]
            out += string[i]
    return out.strip()
def string_run_decompress(data):
    curr = ""
    for c in data:
        if c.islower():
            curr += c
        else:
            if curr: yield curr
            for i in range(b64.find(c)):
                curr = curr[:-1]
    yield curr

def make_save(claims):
    claims_map = [{}, {}, {}]
    sdictionary = set()
    for i, C in enumerate(claims):
        for k, c in enumerate(C):
            c = {w for w in c if w.isalpha()}
            for w in c:
                claims_map[i][w] = k
            sdictionary |= set(c)

    dictionary = sorted(sdictionary)
    claim, exist = [], []
    for w in dictionary:
        for i in range(3):
            if w in claims_map[i]:
                claim.append(claims_map[i][w])
                exist.append(1)
            else:
                claim.append(0)
                exist.append(0)

    assert list(string_run_decompress(string_run_compress(dictionary))) == dictionary
    return string_run_compress(dictionary), b64_collapse(claim, 2), b64_collapse(exist, 1)
    #return [[' '.join(c) for c in C] for C in claims]

save = repr(make_save(claims))
with open("claims_save.txt", "w") as f:
    f.write(save)
print(f"cost: ~{len(save)}B")

from pistestgen import gen

def rhyme_coefficient(text):
    words = [w.strip(".,?!;'\"()[]-") for w in text.lower().split()]
    words = [w for w in words if w]
    et = {}
    d = 0
    gap = 7
    for i in range(len(words)):
        ed = words[i][-3:]
        if ed in et and et[ed] >= i - gap and words[i] != words[et[ed]]:
            d += 1
        et[ed] = i
    d = d / len(words) * gap
    return d

def isvowel(c):
    return c.lower() in "aeiouy"
def count_vowels(text):
    return sum(isvowel(c) for c in text)
def count_diftongs(text):
    return sum((a+b) in ("ie", "ia", "au") for a, b in zip(text, text[1:]))
def upper_vowel_distance(text):
    U = [i for i, c in enumerate(text) if c.isupper()]
    V = [count_vowels(text[U[i]:U[i+1]]) - count_diftongs(text[U[i]:U[i+1]]) for i in range(len(U)-1)]
    return V
def trzynastozgloskowiec_rating(text):
    V = upper_vowel_distance(text)
    S = [0]
    for v in V: S.append(S[-1] + v)
    result = 0
    a = 0
    for b in range(1, len(V)+1):
        while S[b-a] > 14:
            a += 1
        if 12 <= S[b-a] <= 14:
            result += 1
    return 100 * result / count_vowels(text)


x, y = gen(4, 3000)
wrongcnt = {}
ok = 0
total = 0
weights = [1, 2, 6, 65536]

print(flush=True)
oprint = print

upcnt = [0, 0, 0]

ends = defaultdict(list)

#print = lambda *args, **kwargs: None
for k in tqdm.tqdm(range(len(x))):
    words = get_words(x[k])
    #print(x[k])
    #print(y[k], "->", f"@{rhyme_coefficient(x[k]):.2f}, {upper_vowel_distance(x[k])}->{trzynastozgloskowiec_rating(x[k])}")
    decision = []
    clcnts = []
    for i in range(3):
        clcnt = [0 for _ in range(4)]
        for l, c in enumerate(claims[i]):
            for w in words:
                if w in c:
                    clcnt[l] += 1
        clcnts.append(clcnt)
        decision.append(sum(g*v for g, v in zip(weights, clcnt)))
    upper_c = sum(c.isupper() for c in x[k]) / len(words)
    if upper_c >= 0.04:
        decision[0] += 8
        decision[1] += 4
    if rhyme_coefficient(x[k]) >= 0.5:
        decision[0] += 16
    elif len(words) >= 50:
        decision[0] -= 32
    if len(words) >= 15:
        decision[0] += 2*trzynastozgloskowiec_rating(x[k])
    decision[2] += 6
    decision[1] += min(64, max(0, x[k].count("...")-2)*8)/2
    decision[1] += min(64, max(0, x[k].count(" - ")-2)*8)/16
    Y = decision.index(max(decision))
    #for i in range(3):
    #    print("", clcnts[i], end=" ")
    #    if i == names.index(y[k]):
    #        print("!!", end=" ")
    #    if Y == i:
    #        print("??", end=" ")
    #    print()

    if Y == names.index(y[k]):
        ok += 1
    else:
        if y[k] not in wrongcnt:
            wrongcnt[y[k]] = 0
        wrongcnt[y[k]] += 1
    total += 1

    upcnt[names.index(y[k])] += sum(c.isupper() for c in x[k]) / len(words)

splexpr = "', '"

print(f"{ok/total*100:.3f}% !!")
print("wrongs:", wrongcnt)
print(f"uppers: {[v/total for v in upcnt]}")
