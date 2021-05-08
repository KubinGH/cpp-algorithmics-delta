#include <bits/stdc++.h>

using namespace std;

template<typename T>
T mex(vector<T> vec)
{
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    vec.erase(vec.begin(), lower_bound(vec.begin(), vec.end(), 0));
    for(size_t i = 0; i < vec.size(); i++)
        if(i != vec[i])
            return i;
    return vec.size();
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    /*
    vector<size_t> W = {0, 1, 2, 3};
    for(size_t t = 0; t < 20; t++)
        W.push_back(mex<size_t>({W.rbegin()[0], W.rbegin()[1], W.rbegin()[2]}));
    */

    size_t t;
    cin >> t;

    while(t --> 0)
    {
        size_t n;
        cin >> n;

        uint r = 0;
        while(n --> 0)
        {
            uint x;
            cin >> x;
            r ^= x % 4;
        }

        cout << (r ? "first" : "second") << '\n';
    }
}
