#include <bits/stdc++.h>
#define MAX 1000000

using namespace std;
typedef unsigned long long int uint64_t;
typedef unsigned int uint32_t;

int main()
{
    uint32_t particles_n, min_value, i, j;
    cin >> particles_n >> min_value;
    if(particles_n == 1)
    {
        printf("0");
        return 0;
    }
    static uint64_t particles[MAX];
    for(i = 0; i < particles_n; i++)
    {
        uint32_t current;
        cin >> current;
        particles[i] = current;
    }
    sort(particles, particles + particles_n);
    static uint64_t diffsums[MAX], psums[MAX];
    for(i = 0; i < particles_n; i++)
    {
        diffsums[i] = (i > 0 ? diffsums[i - 1] : 0) + particles[i] - particles[0];
        psums[i + 1] = psums[i] + particles[i];
    }
    uint64_t total = 0;
    for(i = 1; i < particles_n; i++)
    {
        uint64_t over = particles[i] > min_value ? particles[i] - min_value - 1 : 0;
        uint64_t bound = upper_bound(particles, particles + i + 1, over) - particles;
        total += (i - bound) * min_value;
        total += bound * particles[i] - psums[bound];
    }
    cout << total;
}
