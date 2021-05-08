#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    map<int, size_t> cnt;
    size_t uniq = 0;
    auto push = [&](int x) {
        uniq += (cnt[x]++ == 0);
    };
    auto pop = [&](int x) {
        uniq -= (--cnt[x] == 0);
    };
    auto ok = [&]() {
        return uniq <= k;
    };

    int64_t result = 0;
    for(size_t i = 0, j = 0; i < n; i++)
    {
        while(j < n and ok())
            push(A[j++]);
        if(not ok())
            pop(A[--j]);
        result += j - i;
        if(i < j)
            pop(A[i]);
    }
    cout << result << endl;
}
