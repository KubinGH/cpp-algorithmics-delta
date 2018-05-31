#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 1<<20;

mt19937 gen{random_device{}()};
template<typename T>
T randint(T a, T b) { return uniform_int_distribution<T>{a, b}(gen); }

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
    //cerr.setstate(ios::failbit);
    gen.seed(time(0));
    static uint32_t A[MAX_N], S[MAX_N];
    uint32_t n = randint(1, 128);
    for(uint32_t i = 0; i < n; i++)
    {
        A[i] = randint(0, 1024);
        cerr << A[i] << " ";
    }
    cerr << endl;
    copy(A, A + n, S);
    sort(S, S + n);
    quick_sort(A, A + n);
    cerr << "S: "; for(uint32_t i = 0; i < n; i++)
        cerr << S[i] << " "; cerr << endl;
    cerr << "A: "; for(uint32_t i = 0; i < n; i++)
        cerr << A[i] << " "; cerr << endl;
    for(uint32_t i = 0; i < n; i++)
        assert(A[i] == S[i]);
}
