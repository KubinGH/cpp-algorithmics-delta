import random, string, sys

import tqdm

import pistestgen


def gen(group):
    return pistestgen.main(group, None, '.', random.randint(0, 2**64 - 1))

vowels = set("aeiouy")
def is_vowel(c):
    return c.lower() in vowels

def characterize(name, text, silent=True, print=print):
    if silent:
        print = lambda *args, **kwargs: None
    print(f"!! {name} !!")

    counters = [
        ".?!", " ", ".?!;,'\"-()[]", string.ascii_lowercase, string.ascii_uppercase,
    ] + [a + a.upper() for a in string.ascii_lowercase]

    splitters = ["$", ".?!", " ", string.ascii_uppercase]
    markers = [is_vowel]

    keywords = ['przez', 'tak', 'nie', 'za', 'ktora', 'ale', 'az', '-', 'bardzo', 'gdy', 'tym', 'przy', 'nad', 'jego', 'ktory', 'bylo', 'on', 'lecz', 'sie', 'wokulski', 'panna', 'jako', 'go', 'azeby', 'z', 'w', 'pod', 'mi', 'i', 'wiec', 'byl', 'nawet', 'ja', 'moze', 'rzekl', 'to', 'do', 'sedzia', 'na', 'jest', 'tylko', 'juz', 'jak', 'nim', 'tej', 'ich', 'jej', 'ma', 'co', 'o', 'pani', 'dla', 'ze', 'tu', 'od', 'sie,', 'winicjusz', 'u', 'a', 'mu', 'ten', 'zas', 'pan', 'po', 'bo', 'mnie', 'czy', 'jeszcze', 'ci', 'tam', 'by']

    values = []
    for sp in splitters:
        print(f"=== `{sp}` ===")
        frags = text.split(sp)
        values.append(len(frags) / len(text))
        #values.append(sum(len(f) for f in frags) / len(frags) / len(text))
        print("Fragment count:", len(frags), " /len", sum(len(f) for f in frags) / len(frags))
        print("Counters:")
        for i, cnt in enumerate(counters):
            v = sum(sum(c in cnt for c in frag)/len(frag) for frag in frags) / len(frags)
            print(f"- `{cnt}`:", v)
            values.append(v)
        print("Markers:")
        for mr in markers:
            v = sum(sum(mr(c) for c in frag)/len(frag) for frag in frags) / len(frags)
            print(f"- `{mr}`:", v)
            values.append(v)
        print("Keywords:")
        words = text.split()
        for w in keywords:
            v = words.count(w) / len(words)
            values.append(v)
            print(w, v)
    return values

names = ["Mickiewicz", "Prus", "Sienkiewicz"]
texts = [open(f"{name}.txt", "r").read() for name in names]

redo = len(sys.argv) > 1 and sys.argv[1] == "redo"
if redo:
    char = [characterize(f"{name}", open(f"{name}.txt", "r").read(), False) for name in names]

    st = ""
    for a, b, c in zip(*char):
        print(f"{a:>15.6f} {b:>15.6f} {c:>15.6f}")
        st += (f"{a:>15.6f} {b:>15.6f} {c:>15.6f}\n")
    with open("data.txt", "w") as d:
        d.write(st)

char = [[], [], []]
with open("data.txt", "r") as d:
    data = d.read().strip()
    for a, b, c in [row.split() for row in data.split('\n')]:
        char[0].append(float(a))
        char[1].append(float(b))
        char[2].append(float(c))

verykeywords = [
['ledwie', 'zamek', 'druga', 'zeby', 'ksztalt', 'swoj', 'nieco', 'wzrok', 'tuz', 'calej', 'nasz', 'naprzod', 'drzewa', 'wnet', 'wy', 'wozny', 'rad', 'widac', 'major', 'podkomorzy', 'wtem', 'gosci', 'klucznik', 'rejent', 'bron', 'ziemi', 'hrabia', 'przerwal', 'wolna', 'pierwszy', 'sedzia', 'reku', 'czyli', 'wam', 'dal', 'wszak', 'hrabiego', 'oba', 'mlodziez', 'jacek', 'reka', 'dlugo', 'horeszkow', 'tadeusz', 'pewnie', 'szlachty', 'wojski', 'wiatr', 'sie:', 'srod', 'koniec', 'szlachta', 'niegdys', 'tadeusza', 'zosia', 'glowy', 'asesor', 'nieraz', 'swych', 'gory', 'krzyknal', 'dalej', 'dawniej', 'swym', 'zamku', 'wielka', 'usta', 'czesto', 'gerwazy', 'rykow', 'rownie', 'litwie', 'stad', 'wkolo', 'pomiedzy', 'znak', 'slowo', 'hrabia,', 'slychac', 'dwoch', 'rak', 'dosyc', 'wtenczas', 'rzecz', 'srodku', 'was', 'jeneral', 'niby', 'chociaz', 'wielki', 'robak', 'drugiej', 'stal', 'tylu', 'prawa', 'sedziego', 'panow', 'ksiadz', 'koncu', 'strony', 'wielkie', 'dwie', 'telimena', 'bylem', 'swe'],
['chyba', 'sklep', 'dwu', 'wasowska', 'prosze', 'wokulskiemu', 'razy', 'nareszcie', 'panna', 'izabela', 'mowi', 'tysiecy', 'baron', 'takie', 'swoja', 'odparl', 'patrzac', 'roku', 'maja', 'ach,', 'wokulskiego.', 'stach', 'wiem', 'swego', 'sposob', 'jaki', 'miec', 'pannie', 'pokoju', 'pani', 'ojciec', 'nie,', 'mowie', 'szepnal', 'rzekla', 'ksiaze', 'ile', 'ciagle', 'no', 'zrobil', 'izabeli', ':', 'pozniej', 'zawolala', 'swoje', 'miala', 'wokulski.', 'panny', 'pare', 'okolo', 'ale...', 'no,', 'poniewaz', 'ignacy', 'sie.', 'baronowa', 'swoim', 'wtedy', 'anizeli', 'wszedl', 'myslal', 'rubli,', 'wokulskiego', 'pan,', 'rubli', 'tomasz', 'swoich', 'izabela.', 'dodal', 'dziesiec', 'zdaje', 'panne', 'ochocki', 'rzecki', 'o,', 'starski', 'panu', 'pania', 'odezwal', 'mowila', 'wie,', 'wokulski,', 'przynajmniej', 'moge', 'sklepu', 'zamiast', 'sto', 'troche', 'wokulski', 'drugi'],
['zwrocil', 'albowiem', 'winicjusza', 'wraz', 'zycie', 'nastepnie', 'mysl', 'duszy', 'chrystus', 'przeciw', 'znow', 'jakies', 'swiat', 'beda', 'smierc', 'widok', 'ligii', 'mimo', 'wszystko,', 'cezara.', 'milosc', 'petroniusza', 'lud', 'nero', 'rzymie', 'chwilami', 'poczal', 'akte', 'ursus', 'nowe', 'wsrod', 'cezara', 'zarazem', 'twoja', 'chwila', 'twarzy', 'tym,', 'procz', 'dlatego,', 'wiesz,', 'wprost', 'ligii,', 'cezar', 'dom', 'winicjusza,', 'piotr', 'nimi', 'kolo', 'winicjusz.', 'bym', 'kazal', 'rowniez', 'jakkolwiek', 'winicjusz', 'ludzi,', 'cezara,', 'rzym', 'wprawdzie', 'soba', 'petroniusz.', 'chilo', 'ligie', 'jest,', 'dlatego', 'widocznie', 'poczeli', 'petroniusz', 'pomponia', 'inni', 'obok', 'wowczas', 'mowic', 'ligia', 'wobec', 'ligie,', 'poczela', 'zas,', 'podniosl', 'odrzekl', 'czesc', 'bowiem', 'winicjusz,', 'poczely', 'ci,', 'jakoz', 'mogla', 'lepiej']
]
def msd(st, nd, eps=1e-7):
    return sum((a-b)**2 for (a, b) in zip(st, nd))
def argmin(it):
    return min((v, i) for i, v in enumerate(it))[1]
def pt(t, p):
    if p >= 0.9*t: return 100
    elif p <= t/3: return 0
    else: return 100 * (p - t/3)/(0.9*t - t/3)

def solve(text, expect=None):
    cchar = characterize(":)", text)
    fault = [msd(cchar, char[g]) for g in range(3)]
    if expect == 0:
        print("base:", fault)
    for g in range(3):
        fault[g] -= 0.33 * sum(text.split().count(v) for v in verykeywords[g])
    if expect == 0:
        print(">verykeywords:", fault)
    words = [w.strip(".,?!;'\"()[]-") for w in text.split()]
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

    i1 = argmin(fault)
    if d >= 0.25:
        fault[0] -= 0.66
    else:
        if len(words) > 50:
            fault[0] += 0.25
    if expect == 0:
        print(">rhyme:", fault)
    i2 = argmin(fault)

    return names[argmin(fault)]

mod = [0.2, 0.2, 0.3, 0.3]

su = 0

print(len(char[0]), "characteristics")

tests = 1
for group in [4]: #[1, 2, 3, 4]:
    print(f"Group {group}")
    ok = 0
    okg = {name: 0 for name in names}
    total = 0
    for t in range(tests):
        inputs, outputs = gen(group)
        total += len(inputs)
        answers = []
        for text, out in tqdm.tqdm(zip(inputs, outputs), total=len(inputs)):
            answers.append(solve(text, names.index(out)))
        for a, b in zip(outputs, answers):
            if a != b:
                okg[a] += 1
        ok += sum(a == b for a, b in zip(outputs, answers))
        print(f" Test {t}: {sum(a == b for a, b in zip(outputs, answers))/len(outputs)*100:.2f}%")
    pp = pt(total, ok)*mod[group-1]
    su += pp
    print(f"{group} --> {ok/total*100:.2f}% ({pp:.1f}pkt) {okg}/{total}")

print(f"!! {su:.1f}pkt !!")
