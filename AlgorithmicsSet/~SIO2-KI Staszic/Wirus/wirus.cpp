#include <bits/stdc++.h>

using namespace std;

const size_t MAX_K = 1000000;
const size_t MAX_M = 500001;

template<typename T1, typename T2, typename T3>
void tupleset(tuple<T1, T2, T3>& t, T1 a, T2 b, T3 c)
{
    get<0>(t) = a; get<1>(t) = b; get<2>(t) = c;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t k;
    cin >> k;
    static array<uint32_t, MAX_K> A, B;
    static array<bool, MAX_K> S;
    set<tuple<uint32_t, uint32_t, uint32_t>> L, R;
    for(uint32_t i = 0; i < k; i++)
    {
        cin >> A[i] >> B[i];
        if(A[i] > B[i])
        {
            swap(A[i], B[i]);
            S[i] = true;
        }
        L.emplace(A[i], B[i], i);
        R.emplace(B[i], A[i], i);
    }
    bool ok = true;
    while(ok and not L.empty())
    {
        tuple<uint32_t, uint32_t, uint32_t> p = *L.begin();
        tuple<uint32_t, uint32_t, uint32_t> t1, ti;
        L.erase(L.begin());
        tupleset(t1, get<1>(p), get<0>(p), get<2>(p));
        R.erase(t1);
        bool conn = false;
        auto c = p;
        while(ok and not conn)
        {
            //cerr << "<" << get<0>(c) << ", " << get<1>(c) << "> ";
            tupleset(t1, get<0>(p), get<1>(c), 0u);
            auto itp = L.lower_bound(t1);
            if(itp != L.end()) ti = *itp;
            if(itp != L.end() and get<0>(ti) == get<0>(p) and
                                  get<1>(ti) == get<1>(c))
            {
                conn = true;
                S[get<2>(ti)] = not S[get<2>(ti)];
                //cerr << "<" << get<0>(*itp) << ", " << get<1>(*itp) << "> ";
                tupleset(t1, get<1>(ti), get<0>(ti), get<2>(ti));
                R.erase(t1);
                L.erase(itp);
                continue;
            }
            tupleset(t1, get<1>(c), 0u, 0u);
            auto it = L.lower_bound(t1);
            if(it != L.end()) ti = *it;
            if(it != L.end() and get<0>(ti) == get<1>(c))
            {
                tupleset(t1, get<1>(ti), get<0>(ti), get<2>(ti));
                R.erase(t1);
                L.erase(it);
                c = ti;
                continue;
            }
            auto itr = R.lower_bound(t1);
            if(itr != R.end()) ti = *itr;
            if(itr != R.end() and get<0>(ti) == get<1>(c))
            {
                S[get<2>(ti)] = not S[get<2>(ti)];
                tupleset(t1, get<1>(ti), get<0>(ti), get<2>(ti));
                L.erase(t1);
                R.erase(itr);
                c = ti;
                continue;
            }
            ok = false;
            //cerr << "!@#";
        }
        //cerr << endl;
    }
    if(ok)
    {
        cout << "TAK\n";
        for(uint32_t i = 0; i < k; i++)
            cout << (S[i] ? 'O' : 'Z') << '\n';
    }
    else
        cout << "NIE";
}
