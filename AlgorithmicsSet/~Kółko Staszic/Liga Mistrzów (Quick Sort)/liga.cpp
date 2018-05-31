#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 7e6;

template<typename Iterator, typename Compare>
void quick_sort(Iterator begin, Iterator end, Compare comp)
{
    typedef typename iterator_traits<Iterator>::value_type T;
    Iterator A = begin;
    size_t n = distance(begin, end);
    if(n == 1)
        return;
    T pivot = A[n-1];
    size_t a = 0, b = n - 1;
    while(a < b)
    {
        while(A[a] <= pivot and a < b)
            a++;
        while(A[b] > pivot and a < b)
            b--;
        swap(A[a], A[b]);
    }
    quick_sort(begin, begin+a, comp);
    quick_sort(begin+b, end, comp);
    return;
}
template<typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    typedef typename iterator_traits<Iterator>::value_type T;
    return quick_sort<Iterator, less<T>>(begin, end, less<T>());
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    quick_sort(A, A + n);
    for(uint32_t i = 0; i < n; i++)
        cout << A[i] << " ";
}
