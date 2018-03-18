#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; int64_t s;
    cin >> n >> s;
    unordered_map<int64_t, uint32_t> M;
    M.reserve(n);
    int64_t S = 0;
    uint32_t result = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        int64_t a;
        cin >> a;
        if(M.find(S) == M.end())
            M[S] = i;
        if(M.find(S - s) != M.end())
            result = max(result, i - M[S - s]);
        S += a;
    }
    if(M.find(S - s) != M.end())
        result = max(result, n - M[S - s]);
    if(result == 0)
        cout << "BRAK";
    else
        cout << result;
}
