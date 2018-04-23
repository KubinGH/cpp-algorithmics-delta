#include <bits/stdc++.h>
#define ADD_AVAILABLE(x, i, j) \
    is_available[x] = true; \
    available[x].first = i; \
    available[x].second = j;
#define INTERVAL_SUM(i, j) (S[j+1] - S[i])

using namespace std;

const size_t MAX = 1e6, MAX_E = 2*MAX+1;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<uint32_t, MAX> A;
    static array<uint32_t, MAX+1> S;
    for(uint32_t i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        A[i] = c == 'W' ? 1 : 2;
        S[i+1] = S[i] + A[i];
    }
    static array<uint32_t, 2> best;
    best[S[n]%2] = S[n];
    static array<pair<uint32_t, uint32_t>, 2> best_interval;
    best_interval[S[n]%2].first = 0;
    best_interval[S[n]%2].second = n-1;
    for(uint32_t i = n; i --> 0;)
    {
        if(A[i] == 1)
        {
            if(S[i] > best[S[i]%2])
            {
                best[S[i]%2] = S[i];
                best_interval[S[i]%2].first = 0;
                best_interval[S[i]%2].second = i - 1;
            }
            break;
        }
    }
    for(uint32_t i = 0; i < n; i++)
    {
        if(A[i] == 1)
        {
            uint32_t x = INTERVAL_SUM(i+1, n-1);
            if(x > best[x%2])
            {
                best[x%2] = max(best[x%2], x);
                best_interval[x%2].first = i + 1;
                best_interval[x%2].second = n - 1;
            }
        }
    }
    static array<bool, MAX_E> is_available;
    static pair<uint32_t, uint32_t> available[MAX_E];
    for(uint32_t t = 0; t < 2; t++)
    {
        if(best[t] != 0)
        {
            ADD_AVAILABLE(best[t], best_interval[t].first,
                                   best_interval[t].second)
            uint32_t i, j;
            tie(i, j) = best_interval[t];
            while(i < j)
            {
                if(A[i] == 2)
                    i++;
                else if(A[j] == 2)
                    j--;
                else
                    i++, j--;
                ADD_AVAILABLE(INTERVAL_SUM(i, j), i, j);
            }
        }
    }
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t a;
        cin >> a;
        if(is_available[a])
            cout << available[a].first+1 << " " << available[a].second+1 << "\n";
        else
            cout << "NIE\n";
    }
}
