#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<double, MAX> A;
    double total = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        total += A[i];
    }
    uint32_t begin = 0, end = 0;
    double current = 0, best = total, half = total / 2;
    while(end < n)
    {
        if(current < half)
            current += A[end++];
        else
            current -= A[begin++];
        double t = abs(half - current);
        if(t < best) best = t;
    }
    cout << (uint64_t)(half - best);
}
