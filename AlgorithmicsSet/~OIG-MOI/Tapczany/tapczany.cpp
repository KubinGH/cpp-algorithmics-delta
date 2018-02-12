#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 100000;

struct dt
{
    uint32_t key, value, index;
};

bool dt_less(const dt lhs, const dt rhs)
{
    return lhs.key < rhs.key;
}

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static dt objects[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        scanf("%u %u", &objects[i].key, &objects[i].value);
        objects[i].index = i + 1;
    }
    sort(objects, objects + n, dt_less);
    vector<uint32_t> result;
    uint32_t best_value = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        if(objects[i].value < best_value)
            result.push_back(objects[i].index);
        else if(objects[i].value > best_value)
            best_value = objects[i].value;
    }
    sort(result.begin(), result.end());
    printf("%u\n", result.size());
    for(uint32_t i = 0; i < result.size(); i++)
        printf("%u ", result[i]);

}
