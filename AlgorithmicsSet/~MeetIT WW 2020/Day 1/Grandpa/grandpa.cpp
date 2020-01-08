#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t T;
    cin >> T;
    while(T --> 0)
    {
        size_t n;
        cin >> n;

        char c;
        for(size_t i = 0; i < n; i++)
          for(size_t j = 0; j < n; j++)
        {
            cin >> c;
            if(i == j)
                cout << char(c^1);
        }
        cout << '\n';
    }
}
