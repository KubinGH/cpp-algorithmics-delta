#include <bits/stdc++.h>

using namespace std;

int64_t area(size_t a, size_t b, size_t c)
{
    cout << "1 " << a+1 << " " << b+1 << " " << c+1 << endl;
    int64_t x;
    cin >> x;
    return x;
}

bool ccw(size_t a, size_t b, size_t c)
{
    cout << "2 " << a+1 << " " << b+1 << " " << c+1 << endl;
    int s;
    cin >> s;
    return s == 1;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    size_t o = 1;
    for(size_t i = 2; i < n; i++)
        if(ccw(0, o, i))
            o = i;

    vector<int64_t> A(n);
    for(size_t i = 1; i < n; i++)
        if(i != o)
            A[i] = area(0, o, i);

    size_t p = max_element(A.begin(), A.end()) - A.begin();
    vector<size_t> part[2];
    for(size_t i = 1; i < n; i++)
        if(i != p)
            part[ccw(0, p, i)].push_back(i);

    for(auto k : {0, 1})
    {
        sort(part[k].begin(), part[k].end(), [&](size_t i, size_t j) {
            return A[i] < A[j];
        });
        if(k == 1)
            reverse(part[k].begin(), part[k].end());
    }

    cout << "0 1 ";
    for(auto i : part[0])
        cout << i+1 << ' ';
    cout << p+1 << ' ';
    for(auto i : part[1])
        cout << i+1 << ' ';
    cout << endl;
}
