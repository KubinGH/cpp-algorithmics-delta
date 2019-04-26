#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> A;
vector<int> F;

int lsb(int p)
{
    return p & -p;
}

void delta(int p, int v)
{
    while(p <= n)
    {
        F[p] ^= v;
        p += lsb(p);
    }
}

int get_prefix(int p)
{
    int r = 0;
    while(p)
    {
        r ^= F[p];
        p -= lsb(p);
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int q;
    cin >> n >> q;

    A.resize(n + 1);
    F.resize(n + 1);

    for(int i = 1; i <= n; i++)
    {
        cin >> A[i];
        delta(i, A[i]);
    }

    while(q --> 0)
    {
        string c; int a, b;
        cin >> c >> a >> b;
        if(c == "zamien")
        {
            delta(a, A[a] ^ A[b]);
            delta(b, A[a] ^ A[b]);
            swap(A[a], A[b]);
        }
        else if(c == "czytaj")
            cout << (get_prefix(b) ^ get_prefix(a - 1)) << endl;
    }
}