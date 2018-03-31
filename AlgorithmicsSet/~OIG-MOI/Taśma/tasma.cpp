#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t m;
    cin >> m;
    for(uint32_t mi = 0; mi < m; mi++)
    {
        uint32_t n;
        cin >> n;
        uint32_t first_unique = 0, second_unique = 0;
        uint32_t first_index = -1u, second_index = -1u;
        uint32_t result = 0;
        for(uint32_t i = 0; i < n; i++)
        {
            uint32_t a;
            cin >> a;
            if(first_unique == 0)
                first_unique = a, first_index = i;
            else if(a != first_unique and second_unique == 0)
                second_unique = a, second_index = i;

            if(first_unique != 0 and a != first_unique)
                result = max(result, i - first_index);
            else if(second_unique != 0)
                result = max(result, i - second_index);
        }
        if(result != 0)
            cout << result << '\n';
        else
            cout << "BRAK\n";
    }
}
