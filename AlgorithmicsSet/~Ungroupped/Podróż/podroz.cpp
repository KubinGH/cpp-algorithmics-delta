#include <bits/stdc++.h>

using std::cout; using std::endl;

int binary_search_begin(int* values, int begin, int end, int value)
{
    if(value < values[begin]) return begin - 1;
    if(value > values[end]) return end - 1;
    int middle;
    printf("binary search %d\n", value);
    while(begin < end)
    {
        middle = (begin + end) / 2;
        printf("%d %d %d\n", begin, middle, end);
        if(values[middle] >= value)
            end = middle;
        else
            begin = middle + 1;
    }
    return begin;
}
int binary_search_end(int* values, int begin, int end, int value)
{
    if(value < values[begin]) return begin - 1;
    if(value > values[end]) return end - 1;
    int middle;
    while(begin < end)
    {
        middle = (begin + end + 1) / 2;
        if(values[middle] <= value)
            begin = middle;
        else
            end = middle - 1;
    }
    return begin;
}

int main()
{
    int city_count, question_count;
    static int city_pop[10000000];
    scanf("%d", &city_count);
    for(int i = 0; i < city_count; i++)
    {
        scanf("%d", city_pop+i);
    }
    scanf("%d", &question_count);
    for(int i = 0; i < question_count; i++)
    {
        int minpop, maxpop, minpop_idx, maxpop_idx;
        scanf("%d %d", &minpop, &maxpop);
        minpop_idx = binary_search_begin(city_pop, 0, city_count - 1, minpop);
        maxpop_idx = binary_search_end(city_pop, 0, city_count - 1, maxpop);
        printf("%d -> %d, %d -> %d\n", minpop, minpop_idx, maxpop, maxpop_idx);
        printf("%d\n", maxpop_idx - minpop_idx);
    }
}
