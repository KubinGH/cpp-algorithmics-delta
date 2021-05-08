#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> A(n);
    int64_t sum = 0;
    for(auto& a : A)
        cin >> a, sum += a;

    cout << max(0l, 2 * *max_element(A.begin(), A.end()) - sum) + sum << endl;

}
