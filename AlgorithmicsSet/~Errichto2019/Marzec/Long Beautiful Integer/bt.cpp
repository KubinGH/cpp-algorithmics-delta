#include <bits/stdc++.h>

using namespace std;

string solve(string S, size_t k)
{
    const size_t n = S.size();

    vector<bool> K(n+1, true);
    for(size_t i = k+1; i <= n; i++)
        K[i] = K[i-1] and S[i-1] == S[(i-1)%k];


    string Z;

    for(size_t p = n+1; p --> k; )
    {
        //cout << "try [1] " << p << endl;
        if(K[p])
        {
            //cout << "+" << endl;
            if(p < n and S[p%k] < S[p])
            {
                //cout << ":(" << endl;
                break;
            }


            Z.resize(n, '?');
            copy(S.begin(), S.begin() + p, Z.begin());
            for(size_t i = k; i < n; i++)
                Z[i] = Z[i-k];

            return Z;
        }
    }
    for(size_t p = k; p --> 0; )
    {
        //cout << "try [2] " << p << endl;
        if(S[p] != '9')
        {
            //cout << "+" << endl;
            Z.resize(n, '?');
            copy(S.begin(), S.begin() + p, Z.begin());
            Z[p] = S[p] + 1;
            for(size_t i = p+1; i < k; i++)
                Z[i] = '0';
            for(size_t i = k; i < n; i++)
                Z[i] = Z[i-k];

            return Z;
        }
    }

    //cout << "fallback" << endl;
    Z.resize(n+1, '0');
    for(size_t i = 0; i < n+1; i += k)
        Z[i] = '1';
    return Z;
}

bool is_ok(uint y, size_t k)
{
    auto s = to_string(y);
    for(size_t i = k; i < s.size(); i++)
        if(s[i] != s[i%k])
            return false;
    return true;
}

string brute(uint x, size_t k)
{
    for(uint y = x; true; y++)
        if(is_ok(y, k))
            return to_string(y);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

/*
    size_t n, k;
    cin >> n >> k;

    string S;
    cin >> S;

    cout << solve(S, k) << endl;
*/

    cout << solve("110112", 4) << endl << brute(110112, 4) << endl;

    vector<uint> pretty[16];
    for(size_t k = 1; k < 16; k++)
    {
        cout << "k = " << k << endl;
        for(uint y = 1; y < 3e6; y++)
            if(k < to_string(y).size() and is_ok(y, k))
                pretty[k].push_back(y);
    }

    for(uint x = 1; x < 1e6; x++)
    {
        cout << "x = " << x << ", |x| = " << to_string(x).size() << endl;
        for(size_t k = 1; k < to_string(x).size(); k++)
        {
            auto Y = solve(to_string(x), k);
            auto Y1 = to_string(*lower_bound(pretty[k].begin(), pretty[k].end(), x));

            cout << x << " #" << k << ": " << Y << " / " << Y1 << endl;
            assert(Y == Y1);
        }
    }

}
