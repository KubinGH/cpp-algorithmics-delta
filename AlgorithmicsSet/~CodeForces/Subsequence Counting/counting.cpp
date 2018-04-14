<<<<<<< HEAD
#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e4;
const uint64_t MAX_E = 1e18;

uint32_t flog2(uint32_t n)
{
    return 31 - __builtin_clz(n);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t x; uint64_t d;
    cin >> x >> d;
    bool ok = true;
    static array<uint64_t, MAX> A;
    A[0] = 1; x--;
    uint32_t n = 1;
    for(; ok and x > 0; n++)
    {
        if(n > MAX)
        {
            ok = false;
            break;
        }
        bool pass = true;
        uint32_t k = 0;
        for(uint64_t i = 0; i < 2; i++)
        {
            A[n] = A[n - 1] + i;
            pass = true;
            k = 0;
            for(uint32_t i = n; i --> 0; k++)
            {
                if(A[n] - A[i] >= d)
                {
                    break;
                }
            }
            //cout << k << endl;
            if(k >= 31 or (1u << k) > x)
                pass = false;
            else
                break;
        }
        if(not pass)
        {
            k = 1;
            for(uint32_t i = n; i --> 0; k++)
            {
                A[n] = A[i] + d;
                if(k >= 31 or (1u << k) > x or A[n] < A[n-1])
                {
                    uint64_t a = A[i];
                    //cout << "stop " << k << " " << i << endl;
                    while(i < n and A[i] == a)
                    {
                        k--, i++;
                        //cout << "dec " << k << " " << i << endl;
                    }
                    A[n] = A[i-1] + d;
                    break;
                }
            }
            //cout << k << endl;
        }
        x -= 1u << k;
        //cout << A[n] << " " << k << " " << x << endl;
        if(A[n] >= MAX_E)
        {
            ok = false;
            break;
        }
    }
    if(not ok)
    {
        cout << -1;
    }
    else
    {
        cout << n << '\n';
        for(uint32_t i = 0; i < n; i++)
            cout << A[i] << " ";
    }
}
=======
#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e4;
const uint64_t MAX_E = 1e18;

uint32_t flog2(uint32_t n)
{
    return 31 - __builtin_clz(n);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t x; uint64_t d;
    cin >> x >> d;
    bool ok = true;
    static array<uint64_t, MAX> A;
    A[0] = 1; x--;
    uint32_t n = 1;
    for(; ok and x > 0; n++)
    {
        if(n > MAX)
        {
            ok = false;
            break;
        }
        bool pass = true;
        uint32_t k = 0;
        for(uint64_t i = 0; i < 2; i++)
        {
            A[n] = A[n - 1] + i;
            pass = true;
            k = 0;
            for(uint32_t i = n; i --> 0; k++)
            {
                if(A[n] - A[i] >= d)
                {
                    break;
                }
            }
            //cout << k << endl;
            if(k >= 31 or (1u << k) > x)
                pass = false;
            else
                break;
        }
        if(not pass)
        {
            k = 1;
            for(uint32_t i = n; i --> 0; k++)
            {
                A[n] = A[i] + d;
                if(k >= 31 or (1u << k) > x or A[n] < A[n-1])
                {
                    uint64_t a = A[i];
                    //cout << "stop " << k << " " << i << endl;
                    while(i < n and A[i] == a)
                    {
                        k--, i++;
                        //cout << "dec " << k << " " << i << endl;
                    }
                    A[n] = A[i-1] + d;
                    break;
                }
            }
            //cout << k << endl;
        }
        x -= 1u << k;
        //cout << A[n] << " " << k << " " << x << endl;
        if(A[n] >= MAX_E)
        {
            ok = false;
            break;
        }
    }
    if(not ok)
    {
        cout << -1;
    }
    else
    {
        cout << n << '\n';
        for(uint32_t i = 0; i < n; i++)
            cout << A[i] << " ";
    }
}
>>>>>>> a250622d67dde61caf8e9ad1c65c7cc6b8d1fd07
