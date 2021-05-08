#include <bits/stdc++.h>

using namespace std;

template<typename It, typename T = typename It::value_type, typename Cmp = less_equal<T>>
vector<size_t> next_succ(It first, It last, Cmp cmp = {}, T id = numeric_limits<T>::max())
{
    vector<T> val(first, last); val.push_back(id);
    const size_t n = val.size() - 1;
    vector<size_t> stk = {n}, ret(n);
    for(size_t i = n; i --> 0; )
    {
        while(cmp(val[stk.back()], val[i]))
            stk.pop_back();
        ret[i] = stk.back();
        stk.push_back(i);
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    auto ptr = next_succ(A.rbegin(), A.rend(), greater_equal<int>{}, 0);
    reverse(ptr.begin(), ptr.end());
    for(auto& x : ptr)
        cout << n-x << ' ';
    cout << endl;
}
