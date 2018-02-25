#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string buffer;
    cin >> buffer;
    uint32_t n = buffer.size();
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
    {
        A[i] = buffer[i] - '0';
    }
    uint32_t s = 0;
    static array<uint32_t, 3> M;
    for(uint32_t i = n; i --> 0; )
    {
        s += A[i]; s %= 3;
        M[s]++;
    }
    //for(uint32_t i = 0; i < n; i++)
    //    cout << S[i] << " "; cout << endl;
    //cout << M[0] << " " << M[1] << " " << M[2] << endl;
    uint64_t r = 0;
    for(uint32_t i = n; i --> 0;)
    {
        if(A[i] % 2 == 0)
        {
            r += M[0];
        }
        uint32_t t;
        M[A[i] % 3]--;
        switch(A[i] % 3)
        {
            case 1:
                t = M[0];
                M[0] = M[1]; M[1] = M[2]; M[2] = t;
                break;
            case 2:
                t = M[0];
                M[0] = M[2]; M[2] = M[1]; M[1] = t;
                break;
        }
        //cout << M[0] << " " << M[1] << " " << M[2] << endl;
    }
    cout << r;
}
