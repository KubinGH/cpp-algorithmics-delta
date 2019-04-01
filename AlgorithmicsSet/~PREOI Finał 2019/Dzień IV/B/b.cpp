#include <bits/stdc++.h>

using namespace std;

template<typename T, typename BinaryOperation>
struct sparse_table
{
    BinaryOperation F;
    size_t n;
    vector<vector<T>> A;
    template<typename Iterator>
    sparse_table(Iterator first, Iterator last)
    {
        n = distance(first, last);
        A.emplace_back(n);
        copy(first, last, A.back().begin());
        for(size_t k = 1; (1u << k) <= n; k++)
        {
            A.emplace_back(n - (1 << k) + 1);
            for(size_t i = 0; i + (1 << k) <= n; i++)
                A[k][i] = F(A[k-1][i], A[k-1][i+(1<<(k-1))]);
        }
    }
    T operator() (size_t i, size_t j) const
    {
        size_t k = __lg(j - i);
        return F(A[k][i], A[k][j - (1 << k)]);
    }
};

template<typename T>
struct f_max
{
    T& operator() (T& a, T& b) const { return a < b ? b : a; }
    const T& operator() (const T& a, const T& b) const { return a < b ? b : a; }
};
template<typename T>
T identity_element(f_max<T>) { return numeric_limits<T>::min(); }
template<typename T>
struct f_min
{
    T& operator() (T& a, T& b) const { return a > b ? b : a; }
    const T& operator() (const T& a, const T& b) const { return a > b ? b : a; }
};
template<typename T>
T identity_element(f_min<T>) { return numeric_limits<T>::max(); }

template<typename T, typename BinaryOperation>
struct segment_tree
{
    BinaryOperation F;
    size_t w;
    vector<T> values;
    segment_tree(size_t n)
    {
        w = 1 << __lg(2*n - 1);
        values.resize(2 * w, identity_element(F));
    }
    void set(size_t p, T v)
    {
        p += w;
        values[p] = v;
        while(p > 1)
            p /= 2, values[p] = F(values[p*2], values[p*2+1]);
    }
    T get(size_t getL, size_t getR)
    {
        T result = identity_element(F);
        for(getL += w, getR += w+1; getL < getR; getL /= 2, getR /= 2)
        {
            if(getL % 2) result = F(result, values[getL++]);
            if(getR % 2) result = F(result, values[--getR]);
        }
        return result;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n);
    mt19937 gen(time(0) ^ (size_t)(new char));
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    sparse_table<uint32_t, f_max<uint32_t>> T(A.begin(), A.end());

    vector<uint32_t> M; M.reserve(n);
    vector<uint32_t> Q(n+1);
    segment_tree<uint32_t, f_min<uint32_t>> Qt(n+1);
    Q[0] = 0;
    for(uint32_t i = 1; i <= n; i++)
    {
        uint32_t lo = 0, hi = i;
        while(lo < hi)
        {
            uint32_t mid = (lo + hi) / 2;
            if(T(mid, i) == A[i-1])
                hi = mid;
            else
                lo = mid+1;
        }
        while(not M.empty() and A[M.back()] > A[i - 1])
        {
            Qt.set(M.back(), -1u);
            M.pop_back();
        }
        M.push_back(i - 1);
        Qt.set(i - 1, Q[i - 1]);
        Q[i] = Qt.get(lo, i - 1) + 1;
    }
    cout << Q[n] << endl;
}