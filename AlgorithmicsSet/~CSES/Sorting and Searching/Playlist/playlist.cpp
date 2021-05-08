#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    unordered_set<int> seen;
    seen.reserve(4 * n);

    size_t result = 0;
    for(size_t i = 0, j = 0; i < n; i++)
    {
        while(j < n and not seen.count(A[j]))
            seen.insert(A[j++]);
        result = max(result, j - i);
        if(i < j)
            seen.erase(A[i]);
    }

    cout << result << endl;
}
