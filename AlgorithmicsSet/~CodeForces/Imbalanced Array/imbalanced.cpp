#include <bits/stdc++.h>

using namespace std;

template<typename T>
vector<T> vslice(vector<T>& A, size_t first, size_t last)
{
    vector<T> O(last - first);
    copy(A.begin() + first, A.begin() + last, O.begin());
    return O;
}

template<typename T>
T sum_imbalance(vector<T> A)
{
    if(A.size() < 4)
    {
        T result = 0;
        for(size_t i = 0; i < A.size(); i++)
        {
            T mx = A[i];
            for(size_t j = i; j < A.size(); j++)
                result += (mx = max(mx, A[j]));
        }
        return result;
    }
    size_t mid = A.size() / 2;
    T result = sum_imbalance(vslice(A, 0, mid+1))
             + sum_imbalance(vslice(A, mid+1, A.size()));
    vector<T> M(A.size(), numeric_limits<T>::min()), S(A.size()+1, 0);
    for(uint32_t i = mid+1; i < A.size(); i++)
        M[i] = max(M[i-1], A[i]);
    for(uint32_t i = A.size(); i --> mid+1; )
        S[i] = S[i+1] + M[i];
    T mx = A[mid];
    size_t u = 0;
    for(uint32_t i = mid+1; i --> 0; )
    {
        mx = max(mx, A[i]);
        while(u < M.size() and M[u] <= mx) u++;
        result += (u-mid-1)*mx + S[u];
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<int64_t> A(n), At(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i], At[i] = -A[i];
    cout << sum_imbalance(A) + sum_imbalance(At);
}
