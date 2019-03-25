#include <bits/stdc++.h>

using namespace std;

struct monoen { uint32_t x, i; };

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t, n;
    cin >> t >> n;

    deque<monoen> maxQ, minQ;

    uint32_t result = 0;
    for(uint32_t i = 0, j = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;

        while(not maxQ.empty() and maxQ.back().x < a)
            maxQ.pop_back();
        while(not minQ.empty() and minQ.back().x > a)
            minQ.pop_back();

        maxQ.push_back({a, i});
        minQ.push_back({a, i});

        while(maxQ.front().x - minQ.front().x > t)
        {
            j++;
            if(maxQ.front().i < j) maxQ.pop_front();
            if(minQ.front().i < j) minQ.pop_front();
        }
        result = max(result, i - j + 1);
    }

    cout << result;
}
