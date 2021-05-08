#include <bits/stdc++.h>

using namespace std;

int main()
{

    size_t n, x;
    cin >> n >> x;

    vector<size_t> C(n);
    for(auto& c : C)
        cin >> c;
    sort(C.begin(), C.end());

    vector<int> R(x+1, INT_MAX-0xD);
    R[0] = 0;
    for(size_t a = 1; a <= x; a++)
        for(auto c : C)
            if(a >= c)
                R[a] = min(R[a], R[a-c] + 1);

    cout << (R[x] == INT_MAX-0xD ? -1 : R[x]) << '\n';
}
