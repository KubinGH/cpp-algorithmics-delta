#include <bits/stdc++.h>

using namespace std;

bool check(int64_t n, vector<int> A)
{
    for(size_t i = 0; i < A.size(); i++)
    {
        auto m = n + (int64_t)i;
        bool ok = false;
        while(m)
        {
            if(A[i] == m%10)
                ok = true;
            m /= 10;
        }
        if(not ok)
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a, assert(0 <= a and a < 10);

    if(*min_element(A.begin(), A.end()) == *max_element(A.begin(), A.end()))
    {
        auto d = A[0];
        size_t m = 1, k = 1, l = 10;
        while(m < n)
            m *= 10;
        while(k < n)
            l *= 10, k *= 10, k++;
        if(d == 0)
            cout << l << endl;
        else if(d == 9)
            cout << l - k << endl;
        else
            cout << m * d << endl;
        return 0;
    }

    for(int i = 1;; i++)
      if(check(i, A))
    {
        cout << i << endl;
        break;
    }
}
