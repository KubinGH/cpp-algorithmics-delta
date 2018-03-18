#include <bits/stdc++.h>

using namespace std;

typedef tuple<uint32_t, uint32_t, uint32_t> tri_u32;

const size_t MAX_K = 1000000;
const size_t MAX_M = 500001;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t k;
    cin >> k;
    static array<uint32_t, MAX_K> A, B;
    static array<bool, MAX_K> S, D;
    static array<set<tri_u32>, MAX_M> L;
    static array<vector<tri_u32>, MAX_M> R;
    static array<uint32_t, MAX_M> RI;
    for(uint32_t i = 0; i < k; i++)
    {
        uint32_t a, b;
        cin >> a >> b;
        if(a > b)
        {
            swap(a, b);
            S[i] = true;
        }
        L[a].emplace(a, b, i);
        R[b].emplace_back(a, b, i);
        A[i] = a; B[i] = b;
    }
    uint32_t l = k, i = 0;
    bool ok = true;
    while(ok and l > 0)
    {
        static tri_u32 p;
        while(D[i]) i++;
        D[i] = true; l--;
        if(l == 0)
        {
            ok = false; break;
        }
        p = make_tuple(A[i], B[i], i);
        L[get<0>(p)].erase(p);
        bool conn = false, first = true;
        static tri_u32 c;
        c = p;
        while(ok and not conn)
        {
            //cerr << "<" << get<0>(c) << ", " << get<1>(c) << "> ";
            if(not first and get<1>(c) == get<0>(p))
            {
                conn = true;
                break;
            }
            static tri_u32 t;
            t = make_tuple(get<0>(p), get<1>(c), 0u);
            auto itp = L[get<0>(p)].lower_bound(t);
            if(itp != L[get<0>(p)].end()) t = *itp;
            if(itp != L[get<0>(p)].end() and get<0>(t) == get<0>(p) and get<1>(t) == get<1>(c))
            {
                //cerr << "(1):<" << get<0>(t) << ", " << get<1>(t) << "> ";
                conn = true;
                L[get<0>(t)].erase(t);
                S[get<2>(t)] = not S[get<2>(t)];
                D[get<2>(t)] = true;
                l--;
            }
            else if(not L[get<1>(c)].empty())
            {
                //cerr << "(2):";
                t = *L[get<1>(c)].begin();
                L[get<1>(c)].erase(L[get<1>(c)].begin());
                D[get<2>(t)] = true;
                c = t;
                l--;
            }
            else if(RI[get<1>(c)] < R[get<1>(c)].size())
            {
                //cerr << "(3):";
                uint32_t& ri = RI[get<1>(c)];
                while(ri < R[get<1>(c)].size() and D[get<2>(R[get<1>(c)][ri])]) ri++;
                if(ri == R[get<1>(c)].size()) goto fail;
                t = R[get<1>(c)][ri];
                L[get<0>(t)].erase(t);
                S[get<2>(t)] = not S[get<2>(t)];
                D[get<2>(t)] = true;
                c = t;
                swap(get<0>(c), get<1>(c));
                l--;
            }
            else
            {
            fail:
                ok = false;
                //cerr << "!@#";
            }
            first = false;
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
