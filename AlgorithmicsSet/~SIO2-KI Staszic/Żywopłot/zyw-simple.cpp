#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> A;

const int Fn = 1 << 20;
int F[Fn + 1];

int lsb(int p)
{
    return p & -p;
}

void delta(int p, int v)
{
    while(p <= Fn)
    {
        F[p] += v;
        p += lsb(p);
    }
}

int get_prefix(int p)
{
    int r = 0;
    while(p)
    {
        r += F[p];
        p -= lsb(p);
    }
    return r;
}

int get(int a, int b)
{
    return get_prefix(b) - get_prefix(a - 1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int q;
    cin >> n >> q;

    A.resize(n + 1);

    for(int i = 1; i <= n; i++)
    {
        cin >> A[i];
        delta(A[i], 1);
    }

    while(q --> 0)
    {
        string c;
        cin >> c;
        if(c == "pyt")
        {
            int h;
            cin >> h;
            cout << get(h, Fn) << "\n";
        }
        else if(c == "mod")
        {
            int i, h;
            cin >> i >> h;
            delta(A[i], -1);
            delta(A[i] = h, 1);
        }
    }
}
