#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; int64_t L, R;
    cin >> n >> L >> R; L--;

    vector<int> H(n);
    for(size_t i = 0; i < n; i++)
        cin >> H[i];

    if((size_t)count(H.begin(), H.end(), 1) == n)
    {
        int64_t c = 0;
        for(int64_t a = 1; a <= (int64_t)n; a++)
        {
            for(; L < min(c + ((int64_t)n-a+1), R); L++)
                cout << a << " ";
            c += n-a+1;
        }
    }
    else
    {
        vector<int64_t> arr;
        arr.reserve(n*(n+1)/2);

        for(size_t i = 0; i < n; i++)
        {
            int a = INT_MAX;
            for(size_t j = i+1; j <= n; j++)
            {
                a = min(a, H[j-1]);
                arr.push_back((int64_t) a * (j - i));
            }
        }
        sort(arr.begin(), arr.end());

        for(int i = L; i < R; i++)
            cout << arr[i] << " ";
    }


}
