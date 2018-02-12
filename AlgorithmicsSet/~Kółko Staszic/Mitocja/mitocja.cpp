#include <bits/stdc++.h>
#define TESTING
#define TEST_FILENAME "tests/testa6"
#ifdef TESTING
#include "testhelper.h"
#endif
#define MAX 1000000

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    INIT_TESTER
    uint32_t islands, bridges;
    cin >> islands >> bridges;
    static vector<uint32_t> graph[MAX];
    for(uint32_t i = 0; i < bridges; i++)
    {
        uint32_t a, b;
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    uint32_t visited = 0;
    for(uint32_t i = 0; i < islands; i++)
        if(graph[i].size() > 1)
            visited++;
    cout << islands - visited;
    FINISH_TEST
}
