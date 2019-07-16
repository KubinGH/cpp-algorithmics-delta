#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 3e4, MAX_K = 333;
const uint64_t VMOD = 169831;

template<typename T>
constexpr T log2floor(T n)
    { return (numeric_limits<T>::digits-1) - __builtin_clz(n); }
template<typename T, size_t N, T(*F)(T, T)>
struct fenwick_tree
{
    size_t n = N, t;
    vector<vector<T>> A;
    fenwick_tree() {}
    T& operator[] (size_t i) { return A[0][i]; }
    T operator() (size_t a, size_t b)
    {
        //uint32_t p = log2floor(b - a + 1);
        //return F(A[p][a], A[p][b + 1 - (1 << p)]);
        return *max_element(A[0].begin()+a, A[0].begin()+b+1);
    }
};
uint64_t max_u64(uint64_t a, uint64_t b) { return a>b ? a : b; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint64_t V[MAX_K];
    uint64_t p = 1, mn = 256*n;
    uint32_t ln = log2floor(n);
    for(uint32_t i = 0; i < MAX_K; i++)
    {
        V[i] = (p + mn) % VMOD;
        p *= 2; p %= VMOD;
    }
    static vector<uint32_t> children[MAX_N];
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v;
        children[u].push_back(v);
    }
    vector<uint32_t> topological;
    stack<uint32_t> to_visit;
    to_visit.push(0);
    while(not to_visit.empty())
    {
        uint32_t u = to_visit.top(); to_visit.pop();
        topological.push_back(u);
        for(uint32_t v : children[u])
            to_visit.push(v);
    }
    reverse(topological.begin(), topological.end());
    static fenwick_tree<uint64_t, MAX_K, max_u64> R[MAX_N];
    static uint32_t A[MAX_K], B[MAX_K];
    for(uint32_t k = 0; k < MAX_K; k++)
    {
        uint32_t a = (k+MAX_K-4*ln-k%3) + 128, b = (k+MAX_K+4*ln+k%9) + 128;
        a %= MAX_K; b %= MAX_K;
        if(a > b) b += MAX_K;
        A[k] = a; B[k] = b;
    }
    for(uint32_t u : topological)
    {
        R[u].A.emplace_back(); R[u].A[0].resize(MAX_K, 0);
        for(uint32_t k = 0; k < MAX_K; k++)
        {
            R[u][k] += V[k];
            uint32_t a = A[k], b = B[k];
            //cerr << k << ": " << a << ".." << b << endl;
            for(uint32_t v : children[u])
            {
                if(b < MAX_K)
                    R[u][k] += R[v](a, b);
                else
                    R[u][k] += max(R[v](a, MAX_K-1), R[v](0, b-MAX_K));
            }
        }
        //R[u].init();
        for(uint32_t v : children[u])
            R[v].A.clear(), R[v].A.shrink_to_fit();
        //cerr << "> " << u << endl;
        //for(uint32_t k = 0; k < MAX_K; k++)
        //    cerr << k << ": " << R[u][k]/4096 << endl;
    }
    cout << R[0](0, MAX_K-1);
}
