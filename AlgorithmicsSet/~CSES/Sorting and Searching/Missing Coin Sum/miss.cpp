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

    sort(A.begin(), A.end());
    int64_t r = 1;
    for(auto a : A)
    {
        if(a > r)
            break;
        r += a;
    }
    cout << r << endl;
}
