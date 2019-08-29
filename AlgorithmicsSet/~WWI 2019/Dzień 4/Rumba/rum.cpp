#include <bits/stdc++.h>

using namespace std;

const int oo = INT_MAX / 3;
size_t n;
int a[128], cache[128][128][5];
bool done[128][128][5];
int k;

int K(size_t l, size_t r, int s)
{
    if(l == r)
        return s ? max(k - s, 0) : 0;

    s = min(s, k - 1);

    auto& cell = cache[l][r][s];
    if(done[l][r][s])
        return cell;

    cell = +oo;

    if(s == k - 1)
        cell = min(cell, K(l, r - 1, 0));
    else
        cell = min(cell, K(l, r, s + 1) + 1);

    for(size_t m = l; m + 1 < r; m++)
        if(a[m] == a[r - 1])
            cell = min(cell, K(l, m + 1, s + 1) + K(m + 1, r - 1, 0));

    done[l][r][s] = true;
    return cell;
}

int main()
{
    cin >> n >> k;

    for(size_t i = 0; i < n; i++)
        cin >> a[i];

    cout << K(0, n, 0);
}
