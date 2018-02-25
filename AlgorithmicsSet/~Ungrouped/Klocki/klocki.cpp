#include <bits/stdc++.h>
#define MAX 1000000
#define VAL(x) ((x) ? 1 : -1)

using namespace std;

typedef unsigned int uint32_t;
typedef map<int32_t, int32_t> count_t;

int main()
{
    uint32_t N, i;
    cin >> N;
    static bool color[MAX];
    string buffer;
    cin >> buffer;
    for(i = 0; i < N; i++)
        color[i] = (buffer[i] == 'Z');
    static int32_t run[MAX];
    static int32_t count_cache[2 * MAX + 1];
    int64_t positives = 0;
    for(i = 0; i < N; i++)
    {
        if(i > 0) run[i] = run[i - 1];
        run[i] += VAL(color[i]);
        count_cache[MAX + run[i]]++;
        if(run[i] > 0) positives++;
    }
    int64_t fix = 0, result = 0, d = 0;
    result += positives;
    for(i = 1; i < N; i++)
    {
        if(run[i - 1] + fix > 0) positives--;
        count_cache[MAX + run[i - 1]]--;
        fix -= VAL(color[i - 1]);
        if(color[i - 1])
        {
            d++;
            positives -= count_cache[MAX + d];
        }
        else
        {
            positives += count_cache[MAX + d];
            d--;
        }
        result += positives;
    }
    cout << result;
}
