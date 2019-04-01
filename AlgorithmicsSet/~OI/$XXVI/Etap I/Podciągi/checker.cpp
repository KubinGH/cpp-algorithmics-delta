#include <bits/stdc++.h>

using namespace std;

const char* ALPHABET = "abcdefghijklmnopqrstuvwxyz"
                       "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                       "0123456789";

uint64_t verify(string& it)
{
    vector<uint64_t> ls(256);
    uint64_t d = 1, e = 0;
    for(uint32_t i = 0; i < it.size(); i++)
    {
        size_t c = int(it[i]) - CHAR_MIN;
        e = d;
        d = 2*e - ls[c];
        ls[c] = e;
    }
    return d;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    vector<uint64_t> N(q);
    for(uint32_t i = 0; i < q; i++)
        cin >> N[i];
    for(uint32_t i = 0; i < q; i++)
    {
        string S;
        cin >> S;
        if(S.size() > 1000)
        {
            cerr << "Solution for " << N[i] << " too long" << endl;
            return 2;
        }
        uint64_t m = verify(S);
        if(N[i] != m)
        {
            cerr << "Got " << m << " instead of " << N[i] << endl;
            return 1;
        }
    }
    return 0;
}
