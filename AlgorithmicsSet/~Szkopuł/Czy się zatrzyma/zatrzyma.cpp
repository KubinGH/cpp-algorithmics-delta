#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint64_t n;
    cin >> n;
    cout << (__builtin_popcountll(n) == 1 ? "TAK" : "NIE");
}
