#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

struct dimatrix
{
    uint32_t a, b, c, d;
    uint32_t det() const { return a*d - b*c; }
    uint32_t tr() const { return a + d; }
};

dimatrix operator* (const dimatrix& A, const dimatrix& B)
{
    return {
        A.a*B.a + A.b*B.c, A.a*B.b + A.b*B.d,
        A.c*B.a + A.d*B.c, A.c*B.b + A.d*B.d
    };
}

ostream& operator<< (ostream& out, const dimatrix& m)
{
    return out << "{" << m.a << ", " << m.b << ", " << m.c << ", " << m.d << "}";
}

dimatrix di(size_t value)
{
    static mt19937_64 gen(1337);
    static map<size_t, dimatrix> dicache;
    if(dicache.count(value)) return dicache[value];
    dimatrix M;
    do {
        M.a = gen(); M.b = gen(); M.c = gen(); M.d = gen();
    } while(M.det() % 2 == 0);
    return dicache[value] = M;
}


template<typename Iterator>
uint32_t trace_hash(Iterator first, Iterator last)
{
    size_t n = distance(first, last);
    dimatrix H = {1, 0, 0, 1};
    for(size_t i = 0; i < n; i++, ++first)
        H = H * di(size_t(*first));
    return H.tr();
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m; int p;
    cin >> n >> m >> p;

    map<uint32_t, size_t> counter;
    for(size_t i = 0; i < n; i++)
    {
        vector<int> W(m);
        for(auto& w : W)
            cin >> w;
        sort(W.begin(), W.end());
        W.push_back(p + W.front());
        vector<int> A(m);
        for(size_t j = 0; j < m; j++)
            A[j] = W[j+1] - W[j];
        counter[trace_hash(A.begin(), A.end())]++;
    }

    size_t r = 0;
    for(const auto& [k, v] : counter)
        r += v*(v-1)/2;

    cout << r;
}
