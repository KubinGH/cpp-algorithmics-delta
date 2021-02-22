#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20;


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; int k;
    cin >> n >> k;
    srand(time(0));

    vector<int> A; A.reserve(n);
    for(size_t i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if(x < k)
            A.push_back(x);
    }
    n = A.size();

    sort(A.begin(), A.end());

    size_t result = n;
    

    cout << result << endl;
}
