#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    //srand(time(0));
    uint32_t n;
    cin >> n;
    //n = 1e6;
    static array<uint64_t, MAX> A;
    uint64_t sum = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        //A[i] = (rand() % (1 << 19));
        sum += A[i];
    }
    sort(A.begin(), A.begin() + n);
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
