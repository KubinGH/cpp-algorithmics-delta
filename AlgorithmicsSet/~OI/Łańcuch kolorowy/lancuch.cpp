#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t length, colors;
    cin >> length >> colors;
    static bitset<MAX> is_required;
    static array<uint32_t, MAX> required_count, required_count_values;
    for(uint32_t i = 0; i < colors; i++)
        cin >> required_count_values[i];
    for(uint32_t i = 0; i < colors; i++)
    {
        uint32_t c;
        cin >> c; c--;
        is_required[c] = true;
        required_count[c] = required_count_values[i];
    }
    static array<uint32_t, MAX> A, current_count;
    uint32_t i = 0, j;
    uint32_t fulfilled = length - colors, result = 0;
    for(j = 0; j < length; j++)
    {
        cin >> A[j]; A[j]--;
        if(current_count[A[j]] == required_count[A[j]])
            fulfilled--;
        current_count[A[j]]++;
        if(current_count[A[j]] == required_count[A[j]])
            fulfilled++;
        while(current_count[A[i]] > required_count[A[i]])
        {
            current_count[A[i]]--;
            if(current_count[A[i]] == required_count[A[i]])
                fulfilled++;
            i++;
        }
        if(fulfilled == length)
            result++;
    }
    cout << result;
}
