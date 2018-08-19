#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5000016, MODCOUNT = 1;
const uint64_t MOD[2] = {
    (1LLU << 63), 1125899906842679LLU
};
const uint64_t POW3[27] = {
    1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147,
    531441, 1594323, 4782969, 14348907, 43046721, 129140163,
    387420489, 1162261467, 3486784401, 10460353203, 31381059609,
    94143178827, 282429536481, 847288609443, 2541865828329
};

struct phash
{
    uint64_t H[MODCOUNT][27];
    uint64_t S[MODCOUNT][MAX];
    uint64_t hash_char(size_t m, uint64_t c)
    {
        return (POW3[c]%MOD[m] + (2*c*c*c)%MOD[m] + (42*c*c)%MOD[m])%MOD[m];
    }
    template<typename Iterator>
    phash(Iterator begin, Iterator end, uint32_t fix = 0)
    {
        for(uint32_t c = 1; c <= 26; c++)
        {
            for(uint32_t m = 0; m < MODCOUNT; m++)
                H[m][c] = hash_char(m, c);
        }
        for(uint32_t i = 0; begin != end; i++, begin++)
        {
            for(uint32_t m = 0; m < MODCOUNT; m++)
                S[m][i+1] = (S[m][i] + H[m][uint32_t(*begin) + fix]) % MOD[m];
        }
    }
    bool operator() (size_t a, size_t b, size_t x, size_t y) const
    {
        for(uint32_t m = 0; m < MODCOUNT; m++)
            if((MOD[m] + S[m][b+1] - S[m][a])%MOD[m] != (MOD[m] + S[m][y+1] - S[m][x])%MOD[m])
                return false;
        return true;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static char S[MAX];
    cin >> S; uint32_t n = strlen(S);
    static phash H(S, S + n, -('a' - 1));
    vector<uint32_t> D;
    for(uint32_t d = 1; d * d <= n; d++)
    {
        if(n % d == 0)
        {
            D.push_back(d);
            if(n != d * d)
                D.push_back(n / d);
        }
    }
    sort(D.begin(), D.end());
    for(uint32_t d : D)
    {
        bool ok = true;
        for(uint32_t k = 1; (k+1)*d <= n and ok; k++)
            if(not H(0, d-1, k*d, (k+1)*d - 1))
                ok = false;
        if(ok)
        {
            cout << d;
            break;
        }
    }
}
