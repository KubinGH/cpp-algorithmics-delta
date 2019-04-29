#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6 + 10;
int t[MAX];

mt19937 gen{random_device{}()};
template<typename T>
T randint(T a, T b)
    { return uniform_int_distribution<T>{a, b}(gen); }

bool bug(vector<pair<int, int>> e)
{
	int n = e.size() + 1, magic = 0;
	for(int i = 1; i <= n; i++)
        t[i] = 0;
	for(int a, b, i = 1; i < n; ++i) {
		tie(a, b) = e[i-1];
		t[a]++; t[b]++;
		magic += 42 * t[a] - 7 * b;
	}
	int mx = 1;
	for(int i = 2; i <= n; ++i) {
		if(t[i] > t[mx]) mx = i;
		magic += mx;
	}
	if(magic < 0) magic = -magic;
	return magic % 113 == 42;
}

int main()
{
    ofstream out("gen-2.cpp");
    out << "#include <bits/stdc++.h>" << endl;
    out << "using namespace std;" << endl;
    out << "const char* solution[5] = {" << endl;
    for(uint32_t i = 0; i < 5; i++)
    {
        uint32_t lo, hi;
        cout << i << endl;
        if(i == 0)
            lo = 1, hi = 15;
        else if(i == 1)
            lo = 20, hi = 100;
        else if(i == 2)
            lo = 150, hi = 250;
        else if(i == 3)
            lo = 1000, hi = 2000;
        else if(i == 4)
            lo = 500000, hi = 500133;
        int n; vector<pair<int, int>> e;
        int s;
        while(true)
        {
            s = randint(0, 1<<30);
            gen.seed(s);
            e.clear();
            n = randint(lo, hi);
            for(int i = 1; i <= n - 1; i++)
            {
                pair<int, int> c(randint(1, i), i+1);
                if(randint(0, 1) == 1)
                    swap(c.first, c.second);
                e.push_back(c);
            }
            if(bug(e))
                break;
        }
        cout << s << endl;
        out << "    \"" << n << " ";
        for(pair<int, int> p : e)
            out << p.first << " " << p.second << " ";
        out << "\"," << endl;
    }
    out << "};\n"
            "int main() {\n"
            "    uint32_t n;\n"
            "    cin >> n;\n"
            "    cout << solution[n];\n"
            "}";
}
