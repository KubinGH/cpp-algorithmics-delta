#include <bits/stdc++.h>
#define MAX 1000000

using namespace std;
typedef unsigned int uint32_t;

int main()
{
    uint32_t stations_n, measures_n;
    scanf("%u %u", &stations_n, &measures_n);
    static vector<uint32_t> stations[MAX];
    for(uint32_t i = 0; i < measures_n; i++)
    {
        uint32_t station, temperature;
        scanf("%u %u", &station, &temperature); station--;
        stations[station].push_back(temperature);
    }
    for(uint32_t i = 0; i < stations_n; i++)
    {
        vector<uint32_t> current = stations[i];
        if(current.empty())
        {
            printf("STACJA KAPUT\n");
            continue;
        }
        sort(current.begin(), current.end());
        printf("Min%u Max%u ", current[0], current[current.size() - 1]);
        uint32_t sum = 0;
        for(uint32_t j = 0; j < current.size(); j++)
            sum += current[j];
        uint32_t average = sum / current.size();
        uint32_t mid = current.size() / 2;
        uint32_t median = (not current.size() % 2) ? (current[mid] + current[mid + 1]) / 2 : current[mid];
        printf("Sre%u Med%u", average, median);
        for(uint32_t j = 0; j < current.size(); j++)
            printf(" %u", current[j]);
        printf("\n");
    }
}
