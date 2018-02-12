#include <set>
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#define range(X, I) for(I = 0; I < X; I++)
#define MAX 1000000
//#define TESTING
#define TEST_FILENAME "tests/testa3"
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
    static uint32_t heights[MAX];
    static set<uint32_t> graph[MAX];
    static bool done[MAX]; fill(done, done + MAX, false);

    uint32_t people, pairs, i;
    cin >> people >> pairs;

    range(people, i)
        cin >> heights[i];

    range(pairs, i)
    {
        uint32_t first, second;
        cin >> first >> second;
        first--; second--;
        graph[first].insert(second);
        graph[second].insert(first);
    }

    vector< set<uint32_t> > groups;
    while(true)
    {
        uint32_t next = MAX;
        range(people, i)
        {
            if(not done[i])
            {
                next = i;
                break;
            }
        }
        if(next == MAX) break;
        else done[next] = true;
        set<uint32_t> group;
        group.insert(heights[next]);
        stack<uint32_t> to_visit;
        to_visit.push(next);
        cout << "start " << next << endl;
        while(not to_visit.empty())
        {
            uint32_t current = to_visit.top(); to_visit.pop();
            for(set<uint32_t>::iterator it = graph[current].begin(); it != graph[current].end(); ++it)
            {
                if(not done[*it])
                {
                    done[*it] = true;
                    cout << "insert " << *it << " " << "@ " << heights[*it] << endl;
                    group.insert(heights[*it]);
                    to_visit.push(*it);
                }
            }
        }
        groups.push_back(group);
    }
    cout << groups.size() << endl;
    static uint32_t differences[MAX]; fill(differences, differences + MAX, 0);
    range(groups.size(), i)
    {
        cout << *groups[i].rbegin() << " " << *groups[i].begin() << endl;
        differences[i] = *groups[i].rbegin() - *groups[i].begin();
    }
    sort(differences, differences + groups.size());
    range(groups.size(), i)
    {
        cout << differences[i];
        if(i != groups.size() - 1) cout << " ";
    }

#ifdef TESTING
    cin.close();
    cout << endl << "=== $ Expected output $ ===" << endl;
    ifstream expout(TEST_FILENAME ".out");
    cout << expout.rdbuf();
    expout.close();
#endif
}
