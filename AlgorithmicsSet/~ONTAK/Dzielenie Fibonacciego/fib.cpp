#include <bits/stdc++.h>

using namespace std;

vector<int> afix(vector<int> a)
{
    a.insert(a.begin(), 0); a.push_back(0);
    a.insert(a.begin(), 0); a.push_back(0);
#define TRIGET(x0, x1, x2) (a[i]==x0 and a[i+1]==x1 and a[i+2]==x2)
#define TRISET(x0, x1, x2) {a[i]=x0, a[i+1]=x1, a[i+2]=x2;}
    for(size_t i = a.size() - 2; i --> 1; )
    {
        if(TRIGET(0, 2, 0))
        {
            TRISET(0, 0, 1);
            a[i-1]++;
        }
        else if(TRIGET(0, 3, 0))
        {
            TRISET(0, 1, 1);
            a[i-1]++;
        }
        else if(TRIGET(2, 1, 0))
        {
            TRISET(1, 0, 1);
        }
        else if(TRIGET(1, 2, 0))
        {
            TRISET(0, 1, 1);
        }
    }
    for(size_t i = 0; i + 2 < a.size(); i++)
        if(TRIGET(1, 1, 0))
            TRISET(0, 0, 1);
    for(size_t i = a.size() - 2; i --> 0; )
        if(TRIGET(1, 1, 0))
            TRISET(0, 0, 1);

    a[2] += a[1];
    a.erase(a.begin(), a.begin() + 2);
    while(not a.empty() and not a.back())
        a.pop_back();

    return a;
}

vector<vector<int>> as_fib_sum(vector<int> a)
{
    vector<vector<int>> result;
    while(any_of(a.begin(), a.end(), [](int x) { return (bool)x; }))
    {
        vector<int> b(a.size());
        bool skip = false;
        for(size_t i = a.size(); i --> 0; )
        {
            if(not skip and a[i])
            {
                b[i]++;
                a[i]--;
                skip = true;
            }
            else
                skip = false;
        }
        result.push_back(b);
    }
    return result;
}

vector<int> fib_sum(vector<int> a, vector<int> b)
{
    if(a.size() > b.size())
        swap(a, b);
    for(size_t i = 0; i < a.size(); i++)
        b[i] += a[i];
    return afix(b);
}

vector<int> fix(vector<int> a)
{
    auto w = as_fib_sum(a);
    while(w.size() > 1)
    {
        auto x = w.back(); w.pop_back();
        auto y = w.back(); w.pop_back();
        w.push_back(fib_sum(x, y));
    }
    return w.empty() ? vector<int>{} : afix(w[0]);
}

vector<int> divide2(vector<int> a)
{
    for(size_t i = a.size(); i --> 1; )
    {
        if(a[i] % 2)
        {
            a[i]--;
            if(i >= 3)
                a[i-2] += 2, a[i-3]++;
            else if(i == 2)
                a[0] += 3;
            else if(i == 1)
                a[0] += 2;
        }
        a[i] /= 2;
    }
    a[0] /= 2;
    return fix(a);
}

vector<int> divide3(vector<int> a)
{
    for(size_t i = a.size(); i --> 2; )
    {
        auto d = a[i]%3;
        a[i] -= d;
        a[i-1] += d;
        a[i-2] += d;
    }
    if(a.size() > 1 and a[1])
    {
        auto d = a[1]%3;
        a[1] -= d;
        a[0] += 2*d;
    }
    for(size_t i = 0; i < a.size(); i++)
        a[i] /= 3;
    return fix(a);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t z;
    cin >> z;
    while(z --> 0)
    {
        size_t n;
        cin >> n;
        vector<int> a(n);
        for(size_t i = 0; i < n; i++)
            cin >> a[i];

        size_t k;
        cin >> k;

        if(k == 2)
            a = divide2(a);
        else if(k == 3)
            a = divide3(a);

        cout << a.size() << " ";
        for(auto d : a)
            cout << d << " ";
        cout << "\n";
    }
}
