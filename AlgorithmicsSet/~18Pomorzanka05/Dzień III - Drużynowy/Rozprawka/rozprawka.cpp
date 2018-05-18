#include <bits/stdc++.h>

using namespace std;

const size_t MAX_X = 256, MAX_Y = 5;

void ins(array<array<char, MAX_X>, MAX_Y>& A, char c, char o, uint32_t x)
{
    uint32_t y = 0;
    A[y][x] = '.'; A[y][x+1] = '.'; A[y][x+2] =  o ; A[y][x+3] = '.'; A[y][x+4] = '.';
    y++;
    A[y][x] = '.'; A[y][x+1] =  o ; A[y][x+2] = '.'; A[y][x+3] =  o ; A[y][x+4] = '.';
    y++;
    A[y][x] =  o ; A[y][x+1] = '.'; A[y][x+2] =  c ; A[y][x+3] = '.'; A[y][x+4] =  o ;
    y++;
    A[y][x] = '.'; A[y][x+1] =  o ; A[y][x+2] = '.'; A[y][x+3] =  o ; A[y][x+4] = '.';
    y++;
    A[y][x] = '.'; A[y][x+1] = '.'; A[y][x+2] =  o ; A[y][x+3] = '.'; A[y][x+4] = '.';
}

int main()
{
    static array<array<char, MAX_X>, MAX_Y> A;
    uint32_t n;
    cin >> n;
    uint32_t x = 0, p = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        if(i > 0)
        {
            x++;
            for(uint32_t y = 0; y < MAX_Y; y++)
            {
                for(uint32_t ix = 0; ix < 2; ix++)
                    A[y][x+ix] = '.';
            }
            x += 2;
        }
        string S;
        cin >> S;
        bool l = false;
        for(char c : S)
        {
            ins(A, c, p%3==2 ? '*' : '#', x);
            if(p%3 == 0 and l)
            {
                A[2][x] = '*';
            }
            x += 4;
            p++;
            l = true;
        }
    }
    for(uint32_t y = 0; y < MAX_Y; y++)
    {
        for(uint32_t ix = 0; ix < x+1; ix++)
        {
            cout << A[y][ix];
        }
        cout << "\n";
    }
}
