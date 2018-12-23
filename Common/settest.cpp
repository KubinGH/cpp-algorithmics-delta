#include <vector>
#include <iostream>
#include "util/randutil.cpp"
#include "util/chronohelper.cpp"

#include <set>
#include "structures/fenwick_set.cpp"

using namespace std;

const size_t V_count = 1 << 19, L_count = 1 << 24;
const uint32_t A_max = 1 << 22;


/*
|V| = 2^17, |L| = 2^23, |A| = 2^20
ktl::fenwick_set
Total: 1765ms
Construction: 0ms
Inserts: 47ms
Searches: 1702ms
Erases: 16ms

std::set
Total: 1700ms
Construction: 0ms
Inserts: 47ms
Searches: 1622ms
Erases: 31ms

|V| = 2^19, |L| = 2^24, |A| = 2^22
ktl::fenwick_set
Total: 6162ms
Construction: 31ms
Inserts: 296ms
Searches: 5647ms
Erases: 188ms

std::set
Total: 6960ms
Construction: 0ms
Inserts: 203ms
Searches: 6523ms
Erases: 234ms

For greater amount of elements, the fenwick_set starts
to perform better. Albeit for an element range
much greater than the amount of elements the std::set may start
to perform better. Still, keep in mind that the std::set won't
allow manual pointer rebinding (which may be useful when
performing predictable operations).
*/
int main()
{
    ktl_gen.seed(42);
    vector<uint32_t> V; V.reserve(V_count);
    for(uint32_t i = 0; i < V_count; i++)
        V.push_back(randint(1u, A_max));
    vector<uint32_t> L; L.reserve(L_count);
    for(uint32_t i = 0; i < L_count; i++)
        L.push_back(randint(1u, A_max));

    uint64_t start, construction, inserts, searches, erases;
    cout << "Start @ " << (start = millis()) << endl;
    fenwick_set S(A_max);
    cout << "Construction @ " << (construction = millis()) << endl;
    for(auto v : V)
        S.insert(v);
    cout << "Inserts @ " << (inserts = millis()) << endl;
    for(auto v : L)
        volatile uint32_t z = *S.lower_bound(v);
    cout << "Searches @ " << (searches = millis()) << endl;
    for(auto v : V)
        S.erase(v);
    cout << "Erases @ " << (erases = millis()) << endl;

    uint64_t finish = millis();
    cout << "Finish @ " << finish << endl << endl;
    cout << "Total: " << finish - start << "ms" << endl;
    cout << "Construction: " << construction - start << "ms" << endl;
    cout << "Inserts: " << inserts - construction << "ms" << endl;
    cout << "Searches: " << searches - inserts << "ms" << endl;
    cout << "Erases: " << erases - searches << "ms" << endl;
}
