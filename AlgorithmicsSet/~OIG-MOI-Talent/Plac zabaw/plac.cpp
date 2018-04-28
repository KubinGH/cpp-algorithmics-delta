#include <bits/stdc++.h>

using namespace std;
 
typedef unsigned long long int uint64_t;

int main()
{
    uint64_t N, H, G;
    cin >> N >> H >> G;
    cout << (N * (G*G - 16*G*H + 64*H*H)) / (4*N*N + 8*N + 4);
}
