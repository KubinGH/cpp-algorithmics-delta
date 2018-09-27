#include <vector>
#include <stack>
#include <iostream>

using namespace std;

uint32_t log2floor(size_t x) { return 31 - __builtin_clz(x); }
template<typename T, T(*F)(T, T)>
struct power_table
{
    size_t n;
    vector<vector<T>> P;
    template<typename Iterator>
    power_table(Iterator first, Iterator last)
    {
        n = distance(first, last);
        P.emplace_back(n);
        for(uint32_t i = 0; first != last; ++first, i++) P[0][i] = *first;
        for(uint32_t p = 1; (1u << p) <= n; p++)
        {
            P.emplace_back(n - (1u << p) + 1);
            for(uint32_t i = 0; i + (1u << p) <= n; i++)
                P[p][i] = F(P[p-1][i], P[p-1][i + (1u<<(p-1))]);
        }
    }
    T operator() (size_t a, size_t b) const
    {
        uint32_t p = log2floor(b - a + 1);
        return F(P[p][a], P[p][b+1-(1<<p)]);
    }
};
uint32_t max_u32(uint32_t a, uint32_t b) { return a>b ? a : b; }

pair<bool, vector<bool>> solve(const vector<uint32_t>& A)
{
    uint32_t n = A.size();
    vector<uint32_t> I(n);
    for(uint32_t i = 0; i < n; i++)
        I[A[i]-1] = i;
    vector<uint32_t> L(n);
    uint32_t m = 0;
    for(uint32_t a = 0; a < n; a++)
    {
        uint32_t i = I[a];
        L[i] = max(m, i);
        m = L[i];
    }
    power_table<uint32_t, max_u32> T(A.begin(), A.end());
    stack<uint32_t> X, Y;
    X.push(n+1); Y.push(n+2);
    vector<bool> R(n);
    uint32_t lo = 1;
    for(uint32_t i = 0; i < n; i++)
    {
        if(X.top() < A[i] and Y.top() < A[i])
            return {false, R};
        else if(X.top() > A[i] and Y.top() < A[i])
            R[i] = 0, X.push(A[i]);
        else if(X.top() < A[i] and Y.top() > A[i])
            R[i] = 1, Y.push(A[i]);
        else
        {
            stack<uint32_t>* S = X.top() < Y.top() ? &X : &Y;
            uint32_t j = i;
            bool same = true;
            while(A[j] < S->top() and T(j, L[j]) != A[j])
                j = I[T(j, L[j])-1], same = not same;
            if(same)
                R[i] = S == &X, ((S == &X) ? &Y : &X)->push(A[i]);
            else
                R[i] = S != &X, ((S == &X) ? &X : &Y)->push(A[i]);
        }
        while(lo <= n)
        {
            if(X.top() == lo) X.pop(), lo++;
            else if(Y.top() == lo) Y.pop(), lo++;
            else break;
        }
    }
    return {true, R};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++) cin >> A[i];
    auto r = solve(A);
    if(r.first)
    {
        cout << "TAK\n";
        for(uint32_t b : r.second)
            cout << uint32_t(b)+1 << " ";
    }
    else
        cout << "NIE";
}
