#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5;

uint64_t gcd(uint64_t a, uint64_t b)
{
    return __gcd(a, b);
}
uint64_t lcm(uint64_t a, uint64_t b)
{
    return a * b / gcd(a, b);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cerr.setstate(ios::failbit);
    uint64_t n, k;
    cin >> n >> k;
    static array<uint64_t, MAX> A;
    set<uint64_t> S;
    unordered_map<uint64_t, uint64_t> M;
    for(uint64_t i = 0; i < n; i++)
    {
        cin >> A[i];
        A[i] %= k; if(A[i] == 0) A[i] = k;
        M[A[i]]++;
        S.insert(A[i]);
    }
    uint64_t result = 0;
    for(uint64_t a : S)
    {
        uint64_t g = gcd(a, k);
        cerr << "-> " << a << " <" << M[a] << "> " << g << endl;
        for(uint64_t b = ((a*g+k-1)/k)*k/g; b <= k; b += k/g)
        {
            if(M[b] != 0)
            {
                //cerr << b << " <" << M[b] << ">" << endl;
                if(b != a)
                    result += M[a] * M[b];
                else
                    result += M[a] * (M[a] - 1) / 2;
            }
            //else
            //    cerr << b << endl;
        }
    }
    //cerr << result << endl;
    cout << n*(n-1)/2 - result << endl;
}
