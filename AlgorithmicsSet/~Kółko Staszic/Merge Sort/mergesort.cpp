#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 1<<20;

mt19937 gen{random_device{}()};
template<typename T>
T randint(T a, T b) { return uniform_int_distribution<T>{a, b}(gen); }

template<typename Iterator, typename Compare>
void merge_sort(Iterator begin, Iterator end, Compare comp)
{
    typedef typename iterator_traits<Iterator>::value_type T;
    size_t n = distance(begin, end);
    if(n == 1)
        return;
    merge_sort(begin, begin+n/2, comp);
    merge_sort(begin+n/2, end, comp);
    uint32_t i = 0, j = n/2, u = n/2, w = n, q = 0;
    static T temp[MAX_N];
    while(i < u or j < w)
    {
        if(j >= w or (i < u and comp(begin[i], begin[j])))
            temp[q++] = begin[i++];
        else
            temp[q++] = begin[j++];
    }
    for(uint32_t i = 0; i < n; i++)
        begin[i] = temp[i];
    return;
}
template<typename Iterator>
void merge_sort(Iterator begin, Iterator end)
{
    typedef typename iterator_traits<Iterator>::value_type T;
    return merge_sort<Iterator, less<T>>(begin, end, less<T>());
}

int main()
{
    //cerr.setstate(ios::failbit);
    gen.seed(time(0));
    static uint32_t A[MAX_N], S[MAX_N];
    uint32_t n = randint(10, 100);
    for(uint32_t i = 0; i < n; i++)
    {
        A[i] = randint(0, 1<<10);
        cerr << A[i] << " ";
    }
    cerr << endl;
    copy(A, A + n, S);
    sort(S, S + n);
    merge_sort(A, A + n);
    cerr << "S: "; for(uint32_t i = 0; i < n; i++)
        cerr << S[i] << " "; cerr << endl;
    cerr << "A: "; for(uint32_t i = 0; i < n; i++)
        cerr << A[i] << " "; cerr << endl;
    for(uint32_t i = 0; i < n; i++)
        assert(A[i] == S[i]);
}
