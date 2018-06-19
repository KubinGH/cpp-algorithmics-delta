#include <bits/stdc++.h>

using namespace std;

template<typename T>
struct cash_register
{
    T _sum = 0;
    multiset<T> prices;
    void insert(const T& o) { prices.insert(o); _sum += o; }
    void erase(const T& o) { erase(prices.find(o)); }
    void erase(typename multiset<T>::iterator it) { _sum -= *it; prices.erase(it); }
    typename multiset<T>::iterator min() const { return prices.begin(); }
    typename multiset<T>::iterator max() const { return --prices.end(); }
    T sum() const { return _sum; }
    size_t size() const { return prices.size(); }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    cash_register<uint64_t> reg;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t t;
        cin >> t;
        if(t == 0)
            cout << reg.sum() << "/" << reg.size() << endl;
        else if(t == 1)
        {
            uint64_t a;
            cin >> a;
            reg.insert(a);
        }
        else if(t == 2)
        {
            auto it = reg.min();
            cout << *it << "\n";
            reg.erase(it);
        }
        else if(t == 3)
        {
            auto it = reg.max();
            cout << *it << "\n";
            reg.erase(it);
        }
    }
}
