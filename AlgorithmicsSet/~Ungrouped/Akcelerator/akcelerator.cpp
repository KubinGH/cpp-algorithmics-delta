#include <bits/stdc++.h>
#define MAX 100000

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    map<uint32_t, uint32_t> frequency;
    uint32_t particles, questions, i, velocity;
    scanf("%u", &particles);
    for(i = 0; i < particles; i++)
    {
        scanf("%u", &velocity);
        frequency[velocity]++;
    }
    scanf("%u", &questions);
    for(i = 0; i < questions; i++)
    {
        scanf("%u", &velocity);
        printf("%u\n", frequency[velocity]);
    }
}
