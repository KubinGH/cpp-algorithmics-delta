#include <bits/stdc++.h>
#define MAX_BOXES 10000000

int main()
{
    uint32_t box_count;
    static uint32_t sizes[MAX_BOXES];
    scanf("%u", &box_count);
    for(uint32_t i = 0; i < box_count; i++)
    {
        scanf("%u", sizes + i);
    }
    uint32_t question_count;
    scanf("%u", &question_count);
    for(uint32_t i = 0; i < question_count; i++)
    {
        uint32_t csize;
        scanf("%u", &csize);
        uint32_t begin = 0, end = box_count - 1, middle, *result = NULL;
        while(begin < end)
        {
            middle = (begin + end) / 2;
            if(sizes[middle] < csize)
                begin = middle + 1;
            else
                end = middle;
        }
        if(sizes[begin] == csize)
            printf("%u\n", begin + 1);
        else
            printf("Kup pudelko!\n");
    }
}
