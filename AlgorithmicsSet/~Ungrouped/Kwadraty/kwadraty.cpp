#include <bits/stdc++.h>
#define MIN(a, b) ((a) > (b) ? b : a)

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    uint32_t width, height;
    while(true)
    {
        scanf("%u %u", &width, &height);
        if(width == 0 and height == 0) break;
        uint32_t last_area = -1, area = 0;
        while(width == height == 0)
        {
            if(width < height)
            {
                area = width * width;
                height -= width;
            }
            else if(width > height)
            {
                area = height * height;
                width -= height;
            }
            else
            {
                area = width * height;
                width = height = 0;
            }
            if(width == height and area < last_area)
            {
                printf("TAK\n");
                break;
            }
            else if(area >= last_area)
            {
                printf("NIE\n");
                break;
            }
            last_area = area;
        }
    }
}
