// Standard array-based heap with customizable comparator.
// Should perform similarly to std::priority_queue

// Last revision: November 2018

#pragma once

#include <vector>
#include <cstddef>
#include <functional>
#include <algorithm>

using std::vector; using std::size_t;
using std::less; using std::swap;

template<typename T, typename Compare = less<T>>
struct heap
{
    Compare C;
    vector<T> H;
    heap() {}
    template<typename Iterator>
    heap(Iterator first, Iterator last, Compare c = {})
    {
        C = move(c);
        H.reserve(distance(first, last));
        while(first != last)
            insert(*first++);
    }
    heap(Compare c = {}) : heap((T*)0, (T*)0, c) {}
private:
    void sift_up(size_t i)
    {
        while(i and C(H[i], H[(i-1)/2]))
            swap(H[i], H[(i-1)/2]), i = (i-1)/2;
    }
    void sift_down(size_t i)
    {
        bool a, b;
        while((a = (2*i+1 < H.size() and C(H[2*i+1], H[i]))) | (b = (2*i+2 < H.size() and C(H[2*i+2], H[i]))))
        {
            size_t j;
            if(a and b) j = C(H[2*i+1], H[2*i+2]) ? 2*i+1 : 2*i+2;
            else if(a)  j = 2*i+1;
            else if(b)  j = 2*i+2;
            swap(H[i], H[j]);
            i = j;
        }
    }
public:
    void insert(T x)
    {
        H.push_back(x);
        sift_up(H.size()-1);
    }
    void pop()
    {
        swap(H.front(), H.back());
        H.pop_back();
        sift_down(0);
    }
    void reserve(size_t n) { H.reserve(n); }
    const T& top() const { return H[0]; }
    bool empty() const { return H.empty(); }
};
