#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<bool>> board_t;

bool X(int32_t x, int32_t y, int32_t x2, int32_t y2, board_t& A)
{
    bool any = false;
    int32_t n = A.size();
    /*
    for(vector<bool> v : A)
    {
        for(bool a : v)
            cout << a;
        cout << endl;
    } cout << endl;
    */
    if(y > 0)
    {
        bool f = false;
        int32_t iy = y;
        while(not f and iy > 0)
        {
            iy--;
            if(A[x][iy])
                f = true;
        }
        if(f)
        {
            A[x][iy] = false;
            bool r = not X(x2, y2, x, iy, A);
            A[x][iy] = true;
            if(r)
                return true;
        }
    }
    if(y < n - 1)
    {
        bool f = false;
        int32_t iy = y;
        while(not f and iy < n - 1)
        {
            iy++;
            if(A[x][iy])
                f = true;
        }
        if(f)
        {
            A[x][iy] = false;
            bool r = not X(x2, y2, x, iy, A);
            A[x][iy] = true;
            if(r)
                return true;
        }
    }
    if(x > 0)
    {
        bool f = false;
        int32_t ix = x;
        while(not f and ix > 0)
        {
            ix--;
            if(A[ix][y])
                f = true;
        }
        if(f)
        {
            A[ix][y] = false;
            bool r = not X(x2, y2, ix, y, A);
            A[ix][y] = true;
            if(r)
                return true;
        }
    }
    if(x < n - 1)
    {
        bool f = false;
        int32_t ix = x;
        while(not f and ix < n - 1)
        {
            ix++;
            if(A[ix][y])
                f = true;
        }
        if(f)
        {
            A[ix][y] = false;
            bool r = not X(x2, y2, ix, y, A);
            A[ix][y] = true;
            if(r)
                return true;
        }
    }
    if(x > 0 and y > 0)
    {
        bool f = false;
        int32_t ix = x, iy = y;
        while(not f and ix > 0 and iy > 0)
        {
            ix--; iy--;
            if(A[ix][iy])
                f = true;
        }
        if(f)
        {
            A[ix][iy] = false;
            bool r = not X(x2, y2, ix, iy, A);
            A[ix][iy] = true;
            if(r)
                return true;
        }
    }
    if(x < n - 1 and y < n - 1)
    {
        bool f = false;
        int32_t ix = x, iy = y;
        while(not f and ix < n - 1 and iy < n - 1)
        {
            ix++; iy++;
            if(A[ix][iy])
                f = true;
        }
        if(f)
        {
            A[ix][iy] = false;
            bool r = not X(x2, y2, ix, iy, A);
            A[ix][iy] = true;
            if(r)
                return true;
        }
    }
    return false;
}

int main()
{
    for(int32_t n = 2; n <= 10; n++)
    {
        board_t A;
        for(int32_t i = 0; i < n; i++)
        {
            A.emplace_back();
            for(int32_t j = 0; j < n; j++)
                A[i].push_back(true);
        }
        A[0][0] = false;
        A[0][n-1] = false;
        cout << n << ": " << X(0, 0, 0, n-1, A) << endl;
    }
}
