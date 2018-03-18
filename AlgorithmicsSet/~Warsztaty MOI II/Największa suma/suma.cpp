#include <bits/stdc++.h>

using namespace std;;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    int64_t best_so_far = numeric_limits<int64_t>::min(), current_best = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        int64_t a;
        cin >> a;
        current_best = max(current_best + a, a);
        best_so_far = max(best_so_far, current_best);
    }
    cout << best_so_far;
}
