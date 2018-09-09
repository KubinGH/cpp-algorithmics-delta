#include <bits/stdc++.h>

using namespace std;

uint64_t solve(string S)
{
    reverse(S.begin(), S.end());
    static uint64_t DP[20][4][2];
    for(uint32_t i = 0; i < 20; i++)
        for(uint32_t z = 0; z <= 3; z++)
            for(uint32_t s = 0; s < 2; s++)
                DP[i][z][s] = 0;
    if(S.back() == '0')
        DP[S.size()-1][0][1] = 1;
    else
    {
        DP[S.size()-1][0][0] = 1;
        DP[S.size()-1][1][0] = S.back() - '1';
        DP[S.size()-1][1][1] = 1;
    }
    for(uint32_t i = S.size()-1; i --> 0; )
    {
        for(uint32_t z = 0; z <= 3; z++)
        {
            DP[i][z][0] += DP[i+1][z][0];
            if(S[i]!='0')
                DP[i][z][0] += DP[i+1][z][1];
        }
        for(uint32_t z = 1; z <= 3; z++)
        {
            DP[i][z][0] += 9*(DP[i+1][z-1][0]);
            if(S[i] >= '2')
                DP[i][z][0] += uint64_t(S[i]-'1')*DP[i+1][z-1][1];
        }
        for(uint32_t z = (S[i]!='0'); z <= 3; z++)
            DP[i][z][1] += DP[i+1][z-(S[i]!='0')][1];
    }
    uint64_t r = 0;
    for(uint32_t z = 0; z <= 3; z++)
        r += DP[0][z][0];
    return r;
}

template<typename T>
string to_string(const T& v)
{
    stringstream stream;
    stream << v;
    return stream.str();
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    while(t --> 0)
    {
        uint64_t l, r;
        cin >> l >> r;
        cout << solve(to_string(r+1)) - solve(to_string(l)) << "\n";
    }
}
