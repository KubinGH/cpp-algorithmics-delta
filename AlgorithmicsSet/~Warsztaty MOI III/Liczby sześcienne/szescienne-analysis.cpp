#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1u << 17;

uint32_t cube(uint32_t x) { return x * x * x; }

vector<uint32_t> remove_duplicates(vector<uint32_t>& vec)
{
    vector<uint32_t> result;
    sort(vec.begin(), vec.end());
    for(uint32_t i = 0; i < vec.size(); i++)
        if(i == vec.size() - 1 or vec[i] != vec[i+1])
            result.push_back(vec[i]);
    return result;
}
vector<uint32_t> cubic_sums_rec(uint32_t n, uint32_t maxim = 1e5)
{
    vector<uint32_t> result;
    if(maxim == 0 or cube(n) > maxim)
        return result;
    vector<uint32_t> next_with;
    result = cubic_sums_rec(n + 1, maxim);
    result.push_back(cube(n));
    next_with = cubic_sums_rec(n + 1, maxim - cube(n));
    for(uint32_t p : next_with)
        result.push_back(p + cube(n));
    result = remove_duplicates(result);
    return result;
}

int rec_main()
{
    auto result = cubic_sums_rec(1, 1e4);
    uint32_t l = -1u, j = 0;
    for(uint32_t i = 1; i <= 1e4; i++)
    {
        while(j < result.size() and result[j] < i)
            j++;
        if(result[j] != i)
            cout << i << endl;
    }
    return 0;
}

int main()
{
    bitset<MAX> A;
    A[0] = 1;
    for(uint32_t n = 1; cube(n) < MAX; n++)
    {
        uint32_t c = cube(n);
        for(uint32_t i = MAX - c; i --> 0;)
            if(A[i])
                A[i+c] = true;
    }
    for(uint32_t i = 0; i < MAX; i++)
        if(A[i])
            cout << i << " ";
}
