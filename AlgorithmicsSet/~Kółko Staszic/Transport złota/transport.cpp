#include <iostream>
#include <map>
#include <bitset>
#define MAX 10000
#define TESTING
#define TEST_FILENAME "tests/testb6"

#ifdef TESTING
#include <fstream>
#endif

using namespace std;

typedef unsigned int uint32_t;

int main()
{
#ifdef TESTING
    ifstream cin(TEST_FILENAME ".in");
#endif
    uint32_t boxes;
    cin >> boxes;
    map<uint32_t, uint32_t> frequency;
    for(uint32_t q = 0; q < boxes; q++)
    {
        uint32_t n;
        cin >> n;
        uint32_t current, last = 2, bit_index = 0;
        bitset<32> result;
        while(n)
        {
            current = n % 2;
            if(current == last)
            {
                result[bit_index] = current;
                bit_index++;
            }
            last = current;
            n /= 2;
        }
        frequency[result.to_ulong()]++;
    }
    uint32_t max_weight = 0, max_frequency = 0;
    for(map<uint32_t, uint32_t>::iterator it = frequency.begin(); it != frequency.end(); ++it)
    {
        if((it->second > max_frequency) or
           (it->second == max_frequency and it->first < max_weight))
        {
            max_weight = it->first;
            max_frequency = it->second;
        }
    }
    cout << max_weight;
#ifdef TESTING
    cin.close();
    cout << endl << "=== $ Expected output $ ===" << endl;
    ifstream expout(TEST_FILENAME ".out");
    cout << expout.rdbuf();
#endif
}
