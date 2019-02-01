#include <bits/stdc++.h>

using namespace std;

uint32_t n;
vector<uint32_t> R, C;
set<uint64_t> solutions;
uint32_t result = 0;

#define POINT(x, y) (1LLU<<((y)*n+(x)))

bool satisfies(uint64_t sol, bool strong = false)
{
    for(uint32_t x = 0; x < n; x++)
    {
        uint32_t p = 0;
        for(uint32_t y = 0; y < n; y++)
            if(sol & POINT(x, y))
                p++;
        if((strong and p != C[x]) or (not strong and p > C[x]))
            return false;
    }
    for(uint32_t y = 0; y < n; y++)
    {
        uint32_t p = 0;
        for(uint32_t x = 0; x < n; x++)
            if(sol & POINT(x, y))
                p++;
        if((strong and p != R[y]) or (not strong and p > R[y]))
            return false;
    }
    return true;
}

void find_solutions(uint64_t x, uint64_t y, uint64_t sol, bool ret = false)
{
    if(not ret)
    {
        if(x == n-1 and y == n-1)
            find_solutions(x, y, sol, true);
        if(x+1 < n and satisfies(sol | POINT(x+1, y)))
            find_solutions(x+1, y, sol | POINT(x+1, y), false);
        if(y+1 < n and satisfies(sol | POINT(x, y+1)))
            find_solutions(x, y+1, sol | POINT(x, y+1), false);
    }
    else
    {
        if(x == 0 and y == 0 and satisfies(sol, true))
            result++, solutions.insert(sol);
        if(x > 0 and satisfies(sol | POINT(x-1, y)))
            find_solutions(x-1, y, sol | POINT(x-1, y), true);
        if(y > 0 and satisfies(sol | POINT(x, y-1)))
            find_solutions(x, y-1, sol | POINT(x, y-1), true);
    }
}

int main()
{
    cin >> n;
    C.resize(n); R.resize(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> R[i];
    for(uint32_t i = 0; i < n; i++)
        cin >> C[i];
    if(satisfies(POINT(0, 0))) find_solutions(0, 0, POINT(0, 0));
    cout << result;
    for(uint64_t sol : solutions)
    {
        cout << endl;
        for(uint32_t y = 0; y < n; y++, cout << endl)
            for(uint32_t x = 0; x < n; x++)
                cout << ((sol & POINT(x, y)) ? '#' : '.');
        cout << endl;
    }
}
