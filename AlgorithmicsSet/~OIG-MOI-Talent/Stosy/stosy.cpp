#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t a, b;
    cin >> a >> b;
    cout << vector<string>{"Bob", "Alicja"}[max(a, b) - min(a, b) >= 2];
}
