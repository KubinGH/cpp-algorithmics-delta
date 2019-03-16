import sympy
import itertools
import functools
import operator
import os

chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&\'()*+,-./:;?@[]^_`{|}~"
N = 10**4+1
chunk_size = 16
M = 0
E = {0}
O = ""
with open("r.txt", "w") as out:
    def oprint(s):
        global O
        O += s
    wfile = open(f"w{N}.txt", "r")
    wlines = [r.strip() for r in wfile.read().split("\n") if r.strip()]
    all_Fs = [[]]
    for line in wlines:
        n, w = line.split(": ")
        n, w = int(n), int(w)
        F = sympy.factorint(w)
        Fs = sorted(k**v for k, v in F.items())
        while sum(Fs) < n:
            Fs.append(1)
        E |= set(Fs)
        Fs.sort()
        M = max(M, len(Fs))
        all_Fs.append(Fs)
    E = sorted(E)
    oprint(f"string chars = \"{chars}\";\n")
    oprint(f"uint32_t E[] = {{{','.join(str(e) for e in E)}}};\n")
    C = ("0" * (chunk_size - 1)) + "~"
    for line in wlines:
        n, w = line.split(": ")
        n, w = int(n), int(w)
        Fs = all_Fs[n]
        print(f"{n}: {Fs}")
        if n > 1 and [a for a in all_Fs[n-1] if a != 1] == [a for a in all_Fs[n] if a != 1]:
            z1 = all_Fs[n].count(1) - all_Fs[n-1].count(1)
            C += "0" * ((chunk_size-len(str(z1))-2)%chunk_size) + "^" + str(z1)
        else:
            C += "0" * ((chunk_size-len(Fs)-1)%chunk_size)
            C += "".join(chars[E.index(x)] for x in Fs)
        C += "~"
    for c in chars:
        print(c, C.count(c))
    dc = {}
    t = []
    C1 = C
    while C1:
        suf = C1[-chunk_size:]
        C1 = C1[:-chunk_size]
        if suf not in dc:
            dc[suf] = 1
            t.append(suf)
        else:
            dc[suf] += 1
    t.sort(key=lambda k: dc[k], reverse=True)
    d = {}
    for i in range(len(t)):
        d[t[i]] = i
    print(len(d), len(C))
    Cc = ",".join(str(d[C[i:i+chunk_size]]) for i in range(0, len(C), chunk_size))
    oprint(f"uint32_t CompressedCache[] = {{{Cc}}};\n")
    D = ",".join("\"" + t[i] + "\"" for i in range(len(d)))
    oprint(f"string CacheDict[] = {{{D}}};\n")

print(M, sorted(E), len(E))

code_template = f"""\
#include <vector>
#include <algorithm>
#include <cstdint>
#include <iostream>

using namespace std;

{O}

vector<string> split(string x, char s)
{{
    vector<string> res;
    res.emplace_back();
    for(char c : x)
    {{
        if(c == s)
            res.emplace_back();
        else
            res.back() += c;
    }}
    return res;
}}

int main()
{{
    string cache;
    for(auto x : CompressedCache)
        cache += CacheDict[x];
    auto cache_list = split(cache, '~');
    for(auto& s : cache_list)
    {{
        while(s[0] == '0')
            s.erase(s.begin(), s.begin() + 1);
    }}
    uint32_t t;
    cin >> t;
    while(t --> 0)
    {{
        uint32_t n;
        cin >> n;
        uint32_t c = 1;
        vector<uint32_t> result;
        uint32_t add_ones = 0;
        while(cache_list[n][0] == '^')
            add_ones += atoi(cache_list[n].c_str() + 1), n--;
        while(add_ones --> 0)
            cout << (c++) << " ";
        for(auto cx : cache_list[n]) 
        {{
            uint32_t x = E[find(chars.begin(), chars.end(), cx) - chars.begin()];
            if(not x) continue;
            for(uint32_t i = 1; i < x; i++, c++)
                cout << c+1 << " ";
            cout << (++c) - x << " ";
        }}
        cout << endl;
    }}
}}
"""

with open("mak.cpp", "w") as f:
    f.write(code_template)

os.system("g++ mak.cpp -o mak.exe -std=c++11 2> clog.txt")
