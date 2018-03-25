#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6, MAX_E = 1e6;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    //srand(time(0));
    uint32_t n;
    cin >> n;
    //n = 1e6;
    static array<uint32_t, MAX> C;
    uint64_t sum = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        //a = (rand() % (1 << 19));
        C[a]++;
        sum += a;
    }
    static array<uint64_t, MAX> A;
    for(uint32_t k = 0, i = 0; k < MAX_E; k++)
    {
        for(uint32_t l = 0; l < C[k]; l++)
            A[i++] = k;
    }
    uint64_t average = sum / n;
    for(uint32_t i = 0; i < n; i++)
    {
        if(A[i] < average)
        {
            sum += average - A[i];
            uint64_t new_average = sum / n;
            while(new_average > average)
            {
                sum += (new_average - average) * (i + 1);
                average = new_average;
                new_average = sum / n;
            }
        }
    }
    cout << fixed << setprecision(3) << (double)(sum) / (double)(n);
}
