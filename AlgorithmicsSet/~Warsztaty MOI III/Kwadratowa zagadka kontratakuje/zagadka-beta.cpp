#include <bits/stdc++.h>

using namespace std;

uint64_t CACHE[1<<20];

uint64_t ipow(uint64_t a, uint64_t b)
{
    if(b > 2 and CACHE[a] != 0)
        return CACHE[a];
    uint64_t r = 1, pa = a;
    while(b)
    {
        if(b % 2)
            r *= a;
        b /= 2;
        a *= a;
    }
    CACHE[pa] = r;
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n, k;
    cin >> n >> k;
    if(k == 2)
    {
        uint64_t r = 0;
        for(uint64_t i = 1; i * i <= n; i++)
        {
            if(n % i == 0 and i != n/i and (n/i - i) % 2 == 0)
                r++;
        }
        cout << r;
    }
    else
    {
        uint64_t r = 0;
        deque<uint64_t> Q;
        // n + a**k = b**k
        // a**k = b**k - n
        Q.push_back(1);
        for(uint64_t b = 2; true; b++)
        {
            uint64_t b_k = ipow(b, k);
            Q.push_back(b_k);
            if(Q[Q.size()-1] - Q[Q.size()-2] > n)
                break;
            else if(b_k < n)
                continue;
            else
            {
                while(not Q.empty() and Q.front() < b_k - n)
                    Q.pop_front();
                if(Q.front() == b_k - n)
                    r++;
            }
        }
        cout << r;
    }
}
