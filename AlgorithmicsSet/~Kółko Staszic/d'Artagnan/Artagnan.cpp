#include <iostream>
#include <vector>

using namespace std;

int main()
{
    uint64_t a, p;
    cin >> a >> p;
    uint64_t result = a * p;
    vector<uint16_t> digits;
    if(result == 0)
        digits.push_back(0);
    else while(result != 0)
    {
        digits.push_back(result % 10);
        result /= 10;
    }
    for(int16_t i = digits.size() - 1; i > -1; i--)
    {
        cout << digits[i];
        if(i != 0)
            cout << "-";
    }
}
