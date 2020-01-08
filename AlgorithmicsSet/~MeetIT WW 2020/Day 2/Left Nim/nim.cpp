    #include <iostream>

    using namespace std;

    int main()
    {
        size_t n;
        cin >> n;

        size_t x = 0;
        for(size_t i = 0; i < n; i++)
        {
            int a;
            cin >> a;
            if(i == x and a == 1)
                x++;
        }

        cout << ((x + (n==x)) % 2 ? "Emilio" : "Valeria");
    }
