#include <bits/stdc++.h>

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

using namespace std;

int main()
{
    while(true)
    {
        uint16_t length;
        vector<uint32_t> current_vec;
        scanf("%d", &length);
        if(length == 0) break;
        for(uint16_t i = 0; i < length; i++)
        {
            uint32_t current;
            scanf("%d", &current);
            current_vec.push_back(current);
        }
        sort(current_vec.begin(), current_vec.end());
        for(uint16_t i = 0; i < length - 2; i++)
        {
            if(current_vec[i] + current_vec[i + 1] > current_vec[i + 2])
            {
                printf("TAK\n");
                goto after_checks;
            }
        }
        printf("NIE\n");
        after_checks:;
    }
}
