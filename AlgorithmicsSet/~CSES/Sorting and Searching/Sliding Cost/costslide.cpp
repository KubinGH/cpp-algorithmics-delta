#include <bits/stdc++.h>

using namespace std;

template<typename T, typename Cmp>
struct heap
{
    T sum = 0;
    set<pair<T, size_t>, Cmp> val;
    map<size_t, T> mem;

    size_t size() const { return val.size(); }
    bool empty() const { return not size(); }

    void push(size_t i, T x)
    {
        sum += x;
        mem[i] = x;
        val.emplace(x, i);
    }
    T pop(size_t i)
    {
        auto it = mem.find(i); auto x = it->second;
        sum -= x;
        val.erase({x, i});
        mem.erase(it);
        return x;
    }
    pair<T, size_t> top() const
    {
        return *val.begin();
    }
};

template<typename T>
struct medianer_set
{
    heap<T, greater<pair<T, size_t>>> left;
    heap<T, less<pair<T, size_t>>> right;

    size_t size() const { return left.size() + right.size(); }
    bool empty() const { return not size(); }

    void balance()
    {
        while(left.size() < right.size())
        {
            auto [x, j] = right.top();
            right.pop(j); left.push(j, x);
        }
        while(left.size() > right.size()+1)
        {
            auto [x, j] = left.top();
            left.pop(j); right.push(j, x);
        }
    }

    void push(size_t i, T x)
    {
        if(left.empty() or x <= left.top().first)
            left.push(i, x);
        else
            right.push(i, x);
        balance();
    }

    void pop(size_t i)
    {
        if(left.mem.count(i))
            left.pop(i);
        else
            right.pop(i);
        balance();
    }

    pair<T, T> median() const
    {
        auto l = left.top().first;
        if(right.empty())
            return {l, l};
        auto r = right.top().first;
        return {l, r};
    }

    T median_dist() const
    {
        T v = median().first;
        return (T(left.size())*v - left.sum) + (right.sum - T(right.size())*v);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    medianer_set<int64_t> M;
    for(size_t i = 0; i < k; i++)
        M.push(i, A[i]);
    cout << M.median_dist() << ' ';
    for(size_t i = k; i < n; i++)
    {
        M.pop(i - k);
        M.push(i, A[i]);
        cout << M.median_dist() << ' ';
    }
    cout << endl;
}
