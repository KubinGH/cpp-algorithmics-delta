#include <bits/stdc++.h>

using namespace std;

ostream& operator<< (ostream& out, const vector<bool>& A)
{
    for(uint32_t i = 0; i < A.size(); i++)
        out << A[i];
    return out;
}

vector<bool> f(vector<bool>& B, uint64_t _f = 1)
{
    uint32_t n = B.size(), f = _f % n;
    vector<bool> A(n);
    for(uint32_t i = 0; i < n; i++)
        if(B[i]) A[(n+i-f)%n] = not A[(n+i-f)%n], A[(i+f)%n] = not A[(i+f)%n];
    return A;
}
vector<bool> Ft(vector<bool> A, uint64_t k)
{
    while(k --> 0)
        A = f(A);
    return A;
}
vector<bool> F(vector<bool> A, uint64_t k)
{
    for(uint32_t p = 64; p --> 0; )
        if((1llu << p) <= k)
            k -= (1llu << p), A = f(A, (1llu << p));
    return A;
}

vector<bool> g(vector<bool>& B)
{
    uint32_t n = B.size();
    vector<bool> A(n);
    for(uint32_t i = 0; i < n; i++)
    {
        if(B[i])
        {
            if(i)       A[i-1] = not A[i-1];
            if(i<n-1)   A[i+1] = not A[i+1];
        }
    }
    return A;
}
vector<bool> Gt(vector<bool> A, uint64_t k)
{
    while(k --> 0)
        A = g(A);
    return A;
}
vector<bool> G(vector<bool> A, uint64_t k) { return Gt(A, k); }

int main()
{
    ios_base::sync_with_stdio(false);
    uint32_t n; uint64_t k; (void)k;
    cin >> n;
    vector<bool> A(n);
    string S;
    cin >> S;
    for(uint32_t i = 0; i < n; i++)
        A[i] = S[i] == 'o';
    vector<bool> A2(2*n+2);
    copy(A.rbegin(), A.rend(), A2.begin()+1);
    copy(A.begin(), A.end(), A2.begin() + n+2);
    for(uint32_t k = 0; k < n*n; k++)
    {
        cout << k << ": " << endl << G(A, k) << endl;
        auto t = Ft(A2, k);
        for(uint32_t i = n+2; i < 2*n+2; i++)
            cout << t[i]; cout << endl;
    }
    /*
    for(uint32_t m = 0; m < (1u << n); m++)
    {
        for(uint32_t i = 0; i < n; i++)
            A[i] = m & (1u << i);
        cout << A << "\n";
        for(uint64_t k = 0; k < 2*n*n; k++)
        {
            //cout << k << "\n";
            //cout << "+ " << Ft(A, k) << " " << Gt(A, k) << "\n";
            assert(F(A, k) == Ft(A, k));
            //cout << "? " << F(A, k) << " " << G(A, k) << "\n";
            assert(G(A, k) == Gt(A, k));
        }
    }
    */
}
