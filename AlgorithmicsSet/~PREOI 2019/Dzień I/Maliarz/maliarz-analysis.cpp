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

void find_solutions(uint64_t x, uint64_t y, uint64_t sol, bool check = true, bool ret = false)
{
    if(not ret)
    {
        if(x == n-1 and y == n-1)
            find_solutions(x, y, sol, check, true);
        if(x+1 < n and (not check or satisfies(sol | POINT(x+1, y))))
            find_solutions(x+1, y, sol | POINT(x+1, y), check, false);
        if(y+1 < n and (not check or satisfies(sol | POINT(x, y+1))))
            find_solutions(x, y+1, sol | POINT(x, y+1), check, false);
    }
    else
    {
        if(x == 0 and y == 0 and (not check or satisfies(sol, true)))
            result++, solutions.insert(sol);
        if(x > 0 and (not check or satisfies(sol | POINT(x-1, y))))
            find_solutions(x-1, y, sol | POINT(x-1, y), check, true);
        if(y > 0 and (not check or satisfies(sol | POINT(x, y-1))))
            find_solutions(x, y-1, sol | POINT(x, y-1), check, true);
    }
}

int main()
{
    cin >> n;
    find_solutions(0, 0, POINT(0, 0), false);
    cout << result << endl;
    cout << solutions.size() << endl;
    set<pair<vector<uint32_t>, vector<uint32_t>>> S;
    auto all_solutions = solutions; solutions.clear(); result = 0;
    for(uint64_t sol : all_solutions)
    {
        cout << endl;
        for(uint32_t y = 0; y < n; y++, cout << endl)
            for(uint32_t x = 0; x < n; x++)
                cout << ((sol & POINT(x, y)) ? '#' : '.');
        cout << endl;

        vector<uint32_t> r(n), c(n);
        for(uint32_t y = 0; y < n; y++)
            for(uint32_t x = 0; x < n; x++)
                if(sol & POINT(x, y))
                    r[y]++, c[x]++;
        auto p = make_pair(r, c);
        if(S.find(p) != S.end())
            cout << "!!!" << endl;
        else
        {
            S.insert(p);

            R = r;
            C = c;
            solutions.clear(); result = 0;
            find_solutions(0, 0, POINT(0, 0));
            assert(not (result & (result-1)));
        }
    }
    /*
    for(uint64_t sol : solutions)
    {
        cout << endl;
        for(uint32_t y = 0; y < n; y++, cout << endl)
            for(uint32_t x = 0; x < n; x++)
                cout << ((sol & POINT(x, y)) ? '#' : '.');
        cout << endl;
    }
    */
}
