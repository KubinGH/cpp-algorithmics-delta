#include <bits/stdc++.h>
#include <ext/numeric>
#include <ktl/structures/li_chao_tree.cpp>

using namespace std;
using __gnu_cxx::power;

int main()
{
    size_t n;
    cin >> n;

    vector<int64_t> H(n), W(n);
    for(size_t i = 0; i < n; i++)
        cin >> H[i];
    for(size_t i = 0; i < n; i++)
        cin >> W[i];

    line_li_chao_tree<int64_t> T(0, *max_element(H.begin(), H.end()) + 1);

    vector<int64_t> B(n, INT64_MAX);
    auto insert = [&](size_t i) {
        T.insert({-2*H[i], B[i] + power(H[i], 2)});
    };
    B[0] = -W[0];
    insert(0);
    for(size_t i = 1; i < n; i++)
    {
        B[i] = T.get_value(H[i]) + power(H[i], 2) - W[i];
        insert(i);
    }

    cout << accumulate(W.begin(), W.end(), 0ll) + B[n - 1];
}
