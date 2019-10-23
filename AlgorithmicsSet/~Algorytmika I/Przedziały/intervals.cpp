#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t n;
    cin >> n;

    vector<pair<uint, uint>> A(n);
    for(auto& i : A)
        cin >> i.first >> i.second;

    sort(A.begin(), A.end(), [&](pair<uint, uint> lhs, pair<uint, uint> rhs) {
        return tie(lhs.second, lhs.first) < tie(rhs.second, rhs.first);
    });

    uint capture = 0;
    size_t result = 0;
    for(auto i : A)
        if(capture <= i.first)
            capture = i.second, result++;

    cout << result;
}
