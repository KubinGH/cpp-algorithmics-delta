#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 18;

struct query_t { uint32_t L, R; bool t; };

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    static int32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t a;
        cin >> a;
        A[i] = a;
    }
    static query_t queries[MAX];
    for(uint32_t i = 0; i < q; i++)
    {
        cin >> queries[i].L >> queries[i].R >> queries[i].t;
        queries[i].L--; queries[i].R--;
    }
    static int32_t E[MAX];
    copy(A, A + n, E);
    sort(E, E + n);
    uint32_t m = unique(E, E + n) - E;
    uint32_t lo = 0, hi = m;
    while(lo < hi)
    {
        uint32_t mid = (lo + hi) / 2;

        //cout << "== " << mid << " ==" << endl;
        set<uint32_t> Q;
        vector<bool> P(n+1);
        using Qit = set<uint32_t>::iterator;
        auto Qprint = [&]() {
            for(auto p : Q)
                cout << "<" << p << ": " << P[p] << "> ";
            cout << endl;
        }; (void)Qprint;
        Q.insert(0); P[0] = A[0] > E[mid];
        for(uint32_t i = 1; i < n; i++)
            if((A[i-1] > E[mid]) != (A[i] > E[mid]))
                Q.insert(i), P[i] = A[i] > E[mid];
        //Qprint();
        for(uint32_t i = 0; i < q; i++)
        {
            uint32_t L = queries[i].L, R = queries[i].R;
            Qit itL = Q.upper_bound(L), itR = Q.upper_bound(R+1); itL--; itR--;
            Qit itL1 = Q.emplace(L).first; P[L] = P[*itL];
            Qit itR1 = Q.emplace(R+1).first; P[R+1] = P[*itR];
            uint32_t c = 0;
            vector<Qit> to_erase;
            Qit it0, it1;
            for(it0 = it1 = itL1, it1++; it0 != itR1; it0++, it1++)
            {
                to_erase.push_back(it0);
                if(P[*it0])
                    c += *it1 - *it0;
            }
            for(Qit it : to_erase)
                Q.erase(it);
            bool b = 1;
            if(queries[i].t == 0)
                c = (R - L + 1) - c, b = !b;
            if(c > 0)
                Q.insert(L), P[L] = b;
            if(L+c <= R)
                Q.insert(L+c), P[L+c] = !b;
            //Qprint();
        }
        auto itr = Q.upper_bound(n/2); itr--;
        if(P[*itr] == 0)
            hi = mid;
        else
            lo = mid+1;
    }
    cout << E[lo];
}
