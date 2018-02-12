#include <bits/stdc++.h>

using namespace std;

typedef unsigned short uint16_t;
typedef unsigned long long int uint64_t;

int main()
{
    vector<uint64_t> vec;
    uint64_t N, C;
    cin >> N;
    if(N == 1)
    {
        cout << "Andrzej";
        return 0;
    }
    for(uint64_t i = 0; i < N; i++)
    {
        cin >> C;
        vec.push_back(C);
    }
    sort(vec.begin(), vec.end());
    bool D = true;
    for(uint64_t i = 1; i < N; i++)
    {
        if(vec[i] == vec[i - 1])
        {
            i++;
            if(i == N - 1)
            {
                D = false;
                break;
            }
        }
        else
        {
            D = false;
            break;
        }
    }
    cout << (D ? "Blazej" : "Andrzej");
}
