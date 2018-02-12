#include <bits/stdc++.h>
#define MAXF(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

typedef long long int int64_t;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int64_t n;
    cin >> n;
    int64_t best_with_current = 0, best_so_far = 0;
    for(int64_t i = 0; i < n; i++)
    {
        int64_t current;
        cin >> current;
        int64_t temp = best_so_far;
        best_so_far = MAXF(best_with_current, best_so_far);
        best_with_current = temp + current;
    }
    cout << MAXF(best_with_current, best_so_far);
}
