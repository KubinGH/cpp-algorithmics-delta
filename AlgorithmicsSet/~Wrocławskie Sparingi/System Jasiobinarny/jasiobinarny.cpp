#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n;
    cin >> n;
    if(n % 2 == 0)
    {
        cout << "NIE";
        return 0;
    }
    else
    {
        stack<bool> R;
        while(n)
        {
            uint64_t y1 = (n + 1) / 2, y2 = (n - 1) / 2;
            if(y1 % 2 == 1 and y2 != 0)
                R.push(0), n = y1;
            else
                R.push(1), n = y2;
        }
        while(not R.empty())
            cout << (R.top() ? '+' : '-'), R.pop();
    }
}
