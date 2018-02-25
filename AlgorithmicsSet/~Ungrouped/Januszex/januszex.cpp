#include <bits/stdc++.h>
#define MAX_LENGTH 200000
#define FIRST_CHAR 'j'
#define NEXT_CHAR(x) (x == 'j' ? 'a' : (x == 'a' ? 'n' : \
                                       (x == 'n' ? 'u' : \
                                       (x == 'u' ? 's' : \
                                       (x == 's' ? 'z' : \
                                       (x == 'z' ? 'e' : \
                                       (x == 'e' ? 'x' : \
                                       (x == 'x' ? '\0' : '\1'))))))))

using namespace std;

int main()
{
    uint32_t length, questions;
    scanf("%u %u", &length, &questions);
    static char str[MAX_LENGTH + 1];
    scanf("%s", str);
    vector< pair<uint32_t, uint32_t> > cache;
    vector< pair<uint32_t, char> > candidates, questions_v;
    uint32_t min_begin = MAX_LENGTH + 1, max_end = 0;
    for(uint32_t q = 0; q < questions; q++)
    {
        uint32_t begin, end;
        scanf("%u %u", &begin, &end);
        begin--;
        if(min_begin > begin) min_begin = begin;
        if(max_end < end) max_end = end;
        questions_v.push_back(make_pair(begin, end));
    }
    // Create all possible candidates
    for(uint32_t i = min_begin; i < max_end; i++)
    {
        char next = NEXT_CHAR(str[i]);
        if(str[i] == FIRST_CHAR)
        {
            candidates.push_back(make_pair(i, NEXT_CHAR(FIRST_CHAR)));
        }
        for(uint32_t j = 0; j < candidates.size(); j++)
        {
            if(str[i] == candidates[j].second)
            {
                if(next == '\0')
                {
                    cache.push_back(make_pair(candidates[j].first, i));
                    candidates.erase(candidates.begin() + j);
                    j--;
                }
                else
                {
                    candidates[j].second = next;
                }
            }
        }
    }
    candidates.clear();
    sort(cache.begin(), cache.end());
    // Cleanup candidates
    if(not cache.empty()) for(uint32_t i = 0; i < cache.size() - 1; i++)
    {
        for(uint32_t j = i + 1; j < cache.size(); j++)
        {
            if(cache[i].first == cache[j].first or cache[i].second == cache[j].second)
            {
                uint32_t d1 = cache[i].second - cache[i].first, d2 = cache[j].second - cache[j].first;
                if(d1 > d2)
                {
                    cache.erase(cache.begin() + i);
                    i--; j--;
                }
                else
                {
                    cache.erase(cache.begin() + j);
                    i--; j--;
                }
            }
        }
    }
    for(uint32_t q = 0; q < questions; q++)
    {
        uint32_t begin = questions_v[q].first, end = questions_v[q].second;
        uint32_t result = 0;
        uint32_t start = begin;
        for(uint32_t i = 0; i < cache.size(); i++)
        {
            if(cache[i].first < start or cache[i].second > end) continue;
            result++;
            start = cache[i].second;
        }
        printf("%u\n", result);
    }
}
