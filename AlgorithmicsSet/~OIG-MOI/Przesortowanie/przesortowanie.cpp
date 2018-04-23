#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 500000;

template<typename T, size_t SIZE>
struct fvector
{
    array<T, SIZE> A;
    uint32_t t = 0;
    T& operator[] (size_t i) { return A[i]; }
    void push_back(T o) { A[t] = o; t++; }
    size_t size() const { return t; }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    if(k > n)
        k = n;
    //if((uint64_t)n * (uint64_t)k > 1e7)
    //    return 0;
    static array<uint32_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    /*
    for(uint32_t ki = 0; ki < k; ki++)
    {
        for(uint32_t i = 0; i < n - 1; i++)
        {
            if(A[i] > A[i+1])
                swap(A[i], A[i+1]);
        }
    }
    for(uint32_t p = 0; p < n; p++)
        cout << A[p] << " "; cout << endl;
    */
    static fvector<uint32_t, MAX> result;
    set<uint32_t> tail;
    for(uint32_t i = 0; i < k; i++)
        tail.insert(A[i]);
    for(uint32_t i = k; i < n; i++)
    {
        tail.insert(A[i]);
        if(tail.size() > k)
        {
            result.push_back(*tail.begin());
            tail.erase(tail.begin());
        }
    }
    for(uint32_t i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    for(uint32_t x : tail)
        cout << x << " ";
}
