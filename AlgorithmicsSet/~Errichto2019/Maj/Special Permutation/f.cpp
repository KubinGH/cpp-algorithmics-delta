#include <bits/stdc++.h>

using namespace std;

bool sat24(vector<int> seq)
{
    for(size_t i = 0; i+1 < seq.size(); i++)
    {
        auto a = abs(seq[i] - seq[i+1]);
        if(not (2 <= a and a <= 4))
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t t;
    cin >> t;

    map<size_t, vector<int>> done;
    while(t --> 0)
    {
        size_t n;
        cin >> n;

        if(not done.count(n))
        {
            if(n <= 8)
            {
                vector<int> result(n);
                iota(result.begin(), result.end(), 1);
                bool found = false;
                do {
                    if(sat24(result))
                    {
                        found = true;
                        break;
                    }
                } while(next_permutation(result.begin(), result.end()));
                done[n] = found ? result : vector<int>();
            }
            else
            {
                vector<int> result; result.reserve(n);
                int x = 1;
                auto push = [&](int d) {
                    result.push_back(x);
                    x += d;
                };
                if(n % 2)
                {
                    while(x < (int)n-4) push(2);
                    push(3); push(-2); push(3); push(-2); push(-3);
                    while(x >= 1) push(-2);
                }
                else
                {
                    while(x < (int)n-5) push(2);
                    push(3); push(2); push(-3); push(2); push(-3);
                    while(x >= 1) push(-2);
                }
                done[n] = result;
            }
        }

        if(not done[n].empty())
            for(auto x : done[n])
                cout << x << ' ';
        else
            cout << -1;
        cout << endl;
    }
}
