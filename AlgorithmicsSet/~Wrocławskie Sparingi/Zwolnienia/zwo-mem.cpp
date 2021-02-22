#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20;

void leakyshift(bitset<MAX>& curr, size_t l)
{
    size_t k = 0;
    while(k < l)
    {
        auto s = min(k + 1, l - k);
        curr |= curr >> s; k += s;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; int64_t k;
    cin >> n >> k;
    // n = 4; k = 256;
    srand(time(0));

    vector<int> A; A.reserve(n);
    for(size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        // x = 1 + rand() % (k - 1);
        if(x < k)
            A.push_back(x);
    }
    n = A.size();

    sort(A.begin(), A.end());
    vector<bitset<MAX>> pref(n+1), suff(n+1);
    pref[0][0] = true;
    for(size_t i = 0; i < n; i++)
        pref[i+1] = pref[i] | (pref[i] << A[i]);
    suff[n][MAX-1] = true;
    for(size_t i = n; i --> 0; )
        suff[i] = suff[i+1] | (suff[i+1] >> A[i]);

    size_t result = 0;
    for(size_t p = 0; p < n; p++)
    {
        auto curr = suff[p+1] >> (MAX-1 - k + 1);
        leakyshift(curr, A[p] - 1);
        cout << (not (pref[p] & curr).any());
        result += not (pref[p] & curr).any();
    }
    cout << endl;

    cout << result << endl;
}
