#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, d; uint64_t p;
    cin >> n >> p >> d;

    vector<uint64_t> A(n);
    for(auto& a : A)
        cin >> a;
    vector<uint64_t> S(n+1);
    partial_sum(A.begin(), A.end(), S.begin() + 1);

    multiset<uint64_t> D;
    size_t result = 0;
    for(size_t l = 0, r = d-1; l+d <= n; l++)
    {
        bool early = false;
        while(r < n)
        {
            r++;
            D.insert(S[r] - S[r-d]);
            early = true;
            if(S[r] - S[l] - *--D.end() > p)
                break;
            early = false;
        }
        if(early)
            D.erase(D.find(S[r] - S[r-d])), r--;
        //cout << l << ".." << r << ' ' << D << endl;
        result = max(result, r - l);
        D.erase(D.find(S[l+d] - S[l]));
    }

    cout << result << endl;
}
