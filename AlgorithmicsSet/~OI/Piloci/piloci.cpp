#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 3000000;

uint64_t abs_diff(uint64_t a, uint64_t b)
{
    return a > b ? a - b : b - a;
}

uint64_t min(uint64_t a, uint64_t b)
{
    return a < b ? a : b;
}

uint64_t max(uint64_t a, uint64_t b)
{
    return a > b ? a : b;
}

struct monoqueue_up
{
    uint64_t arr[MAX];
    uint64_t begin = 0, end = 0;
    void insert(uint64_t n)
    {
        if(begin == end)
        {
            arr[begin] = n;
            end = begin + 1;
        }
        else if(n > arr[begin])
        {
            arr[begin] = n;
            end = begin + 1;
        }
        else if(n <= arr[end - 1])
        {
            arr[end] = n;
            end++;
        }
    }
    uint64_t front()
    {
        return arr[begin];
    }
    uint64_t back()
    {
        return arr[end];
    }
    void pop_front()
    {
        begin++;
    }
    void pop_back()
    {
        end--;
    }
    bool empty()
    {
        return begin == end;
    }
};

struct monoqueue_down : monoqueue_up
{
    void insert(uint64_t n)
    {
        if(begin == end)
        {
            arr[begin] = n;
            end = begin + 1;
        }
        else if(n < arr[begin])
        {
            arr[begin] = n;
            end = begin + 1;
        }
        else if(n >= arr[end - 1])
        {
            arr[end] = n;
            end++;
        }
    }
};

int main()
{
    uint64_t n, t;
    cin >> t >> n;
    static array<uint64_t, MAX> A;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    static monoqueue_up G;
    static monoqueue_down S;
    G.insert(A[0]); S.insert(A[0]);
    uint64_t begin = 0, end = 1;
    for(uint32_t i = 1; i < n; i++)
    {
        end++;
        while(not G.empty() and abs_diff(A[i], G.front()) > t)
        {
            G.pop_front(); begin++;
        }
        while(not S.empty() and abs_diff(A[i], S.front()) > t)
        {
            S.pop_front(); begin++;
        }
        G.insert(A[i]);
        S.insert(A[i]);
        cout << begin << " : " << end << endl;
    }
}
