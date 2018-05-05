#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 10;

typedef array<bitset<MAX>, MAX> board_t;

void toggle(uint32_t x, uint32_t y, board_t& A, uint32_t n)
{
    A[y][x] = not A[y][x];
    if(x > 0)   A[y][x-1] = not A[y][x-1];
    if(x < n-1) A[y][x+1] = not A[y][x+1];
    if(y > 0)   A[y-1][x] = not A[y-1][x];
    if(y < n-1) A[y+1][x] = not A[y+1][x];
}

int main()
{
    uint32_t n;
    cin >> n;
    board_t B;
    for(uint32_t y = 0; y < n; y++) for(uint32_t x = 0; x < n; x++)
    {
        char c;
        cin >> c;
        B[y][x] = c - '0';
    }
    uint32_t result = -1u;
    for(uint32_t initial = 0; initial < (1 << n); initial++)
    {
        board_t A = B;
        uint32_t current = 0;
        for(uint32_t x = 0; x < n; x++)
            if(initial & (1 << x))
                toggle(x, 0, A, n), current++;
        for(uint32_t y = 0; y < n - 1; y++)
            for(uint32_t x = 0; x < n; x++)
                if(A[y][x])
                    toggle(x, y+1, A, n), current++;
        bool ok = true;
        for(uint32_t y = 0; y < n and ok; y++)
            for(uint32_t x = 0; x < n and ok; x++)
                if(A[y][x])
                    ok = false;
        if(ok == true)
            result = min(result, current);
    }
    cout << (int)result << endl;
}
