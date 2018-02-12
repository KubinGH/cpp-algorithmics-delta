#include <bits/stdc++.h>
#define MAX 2000000

using namespace std;

int main()
{
    uint32_t n, k;
    cin >> n >> k;
    static int32_t A[MAX], S[MAX + 1];
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        if(i > 0) S[i + 1] = S[i];
        S[i + 1] += A[i];
    }
    int32_t best_sum = S[k], current_sum = S[k], last_sum = S[k];
    for(uint32_t i = k; i < n; i++)
    {
        last_sum += A[i] - A[i - k];
        if(current_sum + A[i] > last_sum)
            current_sum += A[i];
        else
            current_sum = last_sum;
        if(current_sum > best_sum)
            best_sum = current_sum;
    }
    if(best_sum > 0)
        cout << "TAK";
    else
        cout << "NIE";
}
