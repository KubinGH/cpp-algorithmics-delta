#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string N;
    cin >> N;
    if(N.size() == 1)
    {
        cout << N;
        return 0;
    }
    char a = N.back(); uint32_t ai = N.size() - 1;
    bool same_till_end = false;
    for(uint32_t i = N.size(); i --> 0;)
    {
        if(N[i] > a)
        {
            a = N[i];
            ai = i;
            same_till_end = true;
        }
        else if(N[i] < a)
            same_till_end = false;
    }
    if(same_till_end)
    {
        uint32_t aj = ai;
        a = N.back(); ai = N.size() - 1;
        for(uint32_t i = N.size(); i --> aj+1;)
        {
            if(N[i] > a)
            {
                a = N[i];
                ai = i;
            }
        }
    }
    uint32_t bi = -1u;
    for(uint32_t i = 0; i < ai; i++)
    {
        if(N[i] < a)
        {
            bi = i;
            break;
        }
    }
    if(bi == -1u)
        cout << N;
    else
    {
        for(uint32_t i = 0; i < N.size(); i++)
        {
            if(i == ai)
                cout << N[bi];
            else if(i == bi)
                cout << N[ai];
            else
                cout << N[i];
        }
    }
}
