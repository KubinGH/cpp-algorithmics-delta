#include <iostream>

using namespace std;
typedef unsigned short int uint16_t;

int main()
{
    uint16_t s1, s2, s3, s4;
    cin >> s1 >> s2 >> s3 >> s4;
    uint16_t S = (s1 + s2 + s3 + s4) / 3;
    cout << S - s1 << " " << S - s2 << " " << S - s3 << " " << S - s4;
}
