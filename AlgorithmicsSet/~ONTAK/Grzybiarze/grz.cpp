#include <bits/stdc++.h>

using namespace std;

const int oo = 2e9;

vector<int> solve(vector<int> A, vector<int> B)
{
    const size_t w = A.size() - 1;

    vector<int> T(w+1), B1(w+1);

    int m = 0;
    for(size_t p = w+1, q = w; p --> 1; )
    {
        A[p] -= min(A[p], m);
        q = min(q, p);
        while(A[p])
        {
            while(B[q] <= 0)
                q--;
            auto d = min(A[p], B[q]);
            m += d;
            T[q] += d;
            A[p] -= d;
            B[q] -= d;
            B1[p] += d;
        }
        m -= T[p];
    }

    for(size_t q = 0; q <= w; q++)
        B[q] += B1[q]; 

    return B;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t h, w;
    cin >> h >> w;

    vector<int> A(w+1), B(w+1);
    B[0] = +oo;

    for(size_t i = 0; i < h; i++)
    {
        for(size_t j = 0; j < w; j++)
            cin >> A[j+1];
        B = solve(A, B);
    }

    cout << (+oo - B[0]) << endl;
}
