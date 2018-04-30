#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5+10;
const int INF = 1 << 30;

int main()
{
    int n;
    scanf("%d ", &n);
    static int A[MAX], S[MAX];
    S[0] += 1e5;
    for(int i = 0; i < n; i++)
    {
        char c;
        scanf("%c", &c);
        if(c == '-')
            A[i] = -1;
        else
            A[i] = 1;
        S[i+1] = S[i] + A[i];
    }
    static int M[2*MAX], R[MAX];
    fill(M, M+2*MAX, INF); fill(R, R+MAX, INF);
    M[S[0]] = 0;
    R[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        R[i] = R[i-1];
        if(M[S[i]] != INF)
            R[i] = max(R[i], R[M[S[i]]] + 1);
        M[S[i]] = i;
    }
    printf("%d", R[n]);
}
