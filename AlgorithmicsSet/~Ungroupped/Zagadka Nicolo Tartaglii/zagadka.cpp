#include <bits/stdc++.h>
#define MAX_X 1000000
#define LEFT(x, p, q) (x)*(((x)*(x)) + (p))
#define RIGHT(x, p, q) (q)
#define SATISFIES(x, p, q) LEFT(x, p, q) == RIGHT(x, p, q)

using namespace std;

typedef unsigned long long int uint64_t;

int main()
{
    uint64_t questions;
    cin >> questions;
    for(uint64_t q = 0; q < questions; q++)
    {
        uint64_t P, Q;
        cin >> P >> Q;
        uint64_t lo = 0, hi = MAX_X;
        bool found = false;
        while(hi - lo > 1)
        {
            uint64_t mid = (lo + hi) / 2;
            if(SATISFIES(mid, P, Q))
            {
                cout << mid << endl;
                found = true;
                break;
            }
            else if(SATISFIES(mid + 1, P, Q))
            {
                cout << mid + 1 << endl;
                found = true;
                break;
            }
            if(LEFT(mid, P, Q) < RIGHT(mid, P, Q))
                lo = mid;
            else
                hi = mid;
        }
        if(not found)
            cout << "NIE" << endl;
    }

}
