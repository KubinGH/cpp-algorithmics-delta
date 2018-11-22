#include <bits/stdc++.h>

using namespace std;

template<typename Iterator, typename Compare, typename T = typename iterator_traits<Iterator>::value_type>
void merge_sort(Iterator first, Iterator last, Compare C, vector<T>& temp)
{
    size_t n = distance(first, last);
    if(n <= 1)
        return;
    merge_sort(first, first+n/2, C, temp);
    merge_sort(first+n/2, last, C, temp);
    uint32_t i = 0, j = n/2, u = n/2, w = n, q = 0;
    while(i < u or j < w)
    {
        if(j >= w or (i < u and C(first[i], first[j])))
            temp[q++] = first[i++];
        else
            temp[q++] = first[j++];
    }
    for(uint32_t k = 0; k < n; k++)
        first[k] = temp[k];
    return;
}
template<typename Iterator, typename Compare, typename T = typename iterator_traits<Iterator>::value_type>
void merge_sort(Iterator first, Iterator last, Compare C)
{
    vector<T> temp(distance(first, last));
    return merge_sort(first, last, C, temp);
}
template<typename Iterator, typename T = typename iterator_traits<Iterator>::value_type>
void merge_sort(Iterator first, Iterator last)
    { return merge_sort(first, last, less<T>()); }

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
    void sift_up(size_t i)
    {
        while(i and C(H[i], H[(i-1)/2]))
            swap(H[i], H[(i-1)/2]), i = (i-1)/2;
    }
    void insert(T x)
    {
        H.push_back(x);
        sift_up(H.size()-1);
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
    void pop()
    {
        swap(H.front(), H.back());
        H.pop_back();
        sift_down(0);
    }
    void reserve(size_t n) { H.reserve(n); }
    const T& top() const { return H[0]; }
    bool empty() { return H.empty(); }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t m, n;
    cin >> m >> n;
    vector<pair<uint32_t, uint32_t>> V(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> V[i].second >> V[i].first;
    merge_sort(V.begin(), V.end());
    heap<uint32_t, greater<uint32_t>> H;
    H.reserve(n);
    uint32_t i = 0, r = 0;
    for(uint32_t h = 1; h <= m; h++)
    {
        while(i < n and V[i].first <= h)
            H.insert(V[i++].second);
        if(not H.empty())
            r += H.top(), H.pop();
    }
    cout << r;
}
