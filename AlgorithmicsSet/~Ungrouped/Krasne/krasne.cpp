#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 200;
const size_t MAX_W = 5000;

uint32_t max(uint32_t a, uint32_t b)
{
    return a > b ? a : b;
}

int main()
{
    uint32_t n, cap;
    cin >> n >> cap;
    array<uint32_t, MAX> weights;
    uint32_t total = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> weights[i];
        total += weights[i];
    }
    sort(weights.begin(), weights.begin() + n);
    array<uint32_t, MAX_W> best;
    for(uint32_t w = 0; w < n; w++)
    {
        for(uint32_t i = cap - weights[w] + 1; i --> 0;)
        {
            if(best[i] != 0)
                best[i + weights[w]] += best[i];
        }
        best[weights[w]]++;
    }
    cout << best[cap];
}
