#include <bits/stdc++.h>

using namespace std;

struct bits_generator
{
    mt19937 gen;
    uint32_t acc = 0, left = 0;
    bool operator() ()
    {
        if(not left)
            left = 32, acc = gen();
        bool o = acc & 1;
        acc >>= 1; left--;
        return o;
    }
};


#ifdef XHOVA
string __M;
uint32_t query(const vector<bool>& S)
{
    uint32_t r = 0;
    cerr << "? ";
    for(uint32_t i = 0; i < S.size(); i++)
    {
        cerr << S[i];
        if(__M[i] - '0' == S[i])
            r++;
    }
    cerr << endl;
    return r == S.size() ? 2 : (r == S.size()/2);
}
#else
uint32_t query(const vector<bool>& S)
{
    for(bool o : S)
        cout << o;
    cout << endl;
    uint32_t r;
    cin >> r;
    return r == S.size() ? 2 : (r == S.size()/2);
}
#endif

int main()
{
    uint32_t n;
#ifdef XHOVA
    cin >> __M;
    n = __M.size();
#else
    cin >> n;
#endif
    bits_generator bit;
    vector<bool> S(n);
    for(uint32_t i = 0; i < n + 500; i++)
    {
        for(uint32_t i = 0; i < n; i++)
            S[i] = bit();
        uint32_t r = query(S);
        if(r == 2)
        {
            cerr << "+" << endl;
            break;
        }
        else if(r == 1)
        {
            cerr << "/" << endl;
        }
        else
        {
            cerr << "-" << endl;
        }
    }
}
