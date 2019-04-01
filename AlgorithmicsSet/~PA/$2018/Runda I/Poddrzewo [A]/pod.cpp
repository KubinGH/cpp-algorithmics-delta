#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    uint32_t o = 0;
    for(uint32_t i = 0; i < n; i++)
        if([]() { uint32_t d; cin >> d; return d; } () == 1) o++;
    if(o >= 2)
        cout << "0\n";
    else if(o == 1)
        cout << "1\n";
    else
        cout << "2\n";
    cout << "2\n1 2";
}
