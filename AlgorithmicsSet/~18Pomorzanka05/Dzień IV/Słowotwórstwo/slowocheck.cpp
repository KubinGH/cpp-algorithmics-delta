#include <bits/stdc++.h>

using namespace std;

int main()
{
    srand(time(0));
    uint32_t n;
    cin >> n;
    for(uint32_t ti = 0; ti < 10000; ti++)
    {
        string S;
        ofstream out("tmp/tmp.in");
        for(uint32_t i = 0; i < n; i++)
            S += char((rand()%2)+'a');
        out << S.size() << "\n" << S;
        cout << S << endl;
        out.close();
        system("slowotworstwo.exe < tmp/tmp.in > tmp/tmp.got.out");
        system("slowotworstwo-brute.exe < tmp/tmp.in > tmp/tmp.exp.out");
        ifstream f_exp("tmp/tmp.exp.out"), f_got("tmp/tmp.got.out");
        stringstream exp, got;
        exp << f_exp.rdbuf(); got << f_got.rdbuf();
        cout << exp.str() << " " << got.str() << endl;
        assert(exp.str() == got.str());
    }
    system("pause");
}
