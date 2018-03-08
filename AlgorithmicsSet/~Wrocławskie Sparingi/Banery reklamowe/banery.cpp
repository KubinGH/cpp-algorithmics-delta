#include <bits/stdc++.h>

using namespace std;

const uint64_t R[10] = {518832049272, 1083140225072,
                        1082540998776, 535804535036,
                        827871513804, 535805037820,
                        518826760240, 51945431292,
                        518826544248, 103892438136};
const uint32_t WIDTH = 8, HEIGHT = 5, TOTAL_WIDTH = 20 * WIDTH;

void write_to(array<array<char, TOTAL_WIDTH>, HEIGHT>& A, uint32_t d,
              uint32_t bx, uint32_t by)
{
    uint64_t s = R[d];
    for(uint32_t y = by; y < by + HEIGHT; y++)
    {
        for(uint32_t x = bx; x < bx + WIDTH; x++)
        {
            s /= 2;
            A[y][x] = s%2 ? '#' : '.';
        }
    }
}

int main()
{
    string n;
    cin >> n;
    static array<array<char, TOTAL_WIDTH>, HEIGHT> A;
    uint32_t bx = 0;
    for(char d : n)
    {
        write_to(A, d - '0', bx, 0);
        bx += WIDTH;
    }
    for(uint32_t y = 0; y < HEIGHT; y++)
    {
        for(uint32_t x = 0; x < bx; x++)
            cout << A[y][x];
        cout << '\n';
    }
}
