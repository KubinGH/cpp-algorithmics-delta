#include <bits/stdc++.h>
#define MAX 1000000

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    static vector<uint32_t> children[MAX];
    static uint32_t total_children[MAX]; // Including sub-children
    fill(total_children, total_children + MAX, 0);
    static bool done[MAX];
    fill(done, done + MAX, false);
    uint32_t k, fcount, qcount;
    scanf("%u", &fcount);
    for(k = 0; k < fcount - 1; k++)
    {
        uint32_t parent, child;
        scanf("%u %u", &parent, &child);
        children[parent - 1].push_back(child - 1);
    }
    scanf("%u", &qcount);
    for(k = 0; k < qcount; k++)
    {
        uint32_t cparent;
        scanf("%u", &cparent); cparent--;
        stack<uint32_t> callstack;
        if(done[cparent]) goto after;
        callstack.push(cparent);
        while(not callstack.empty())
        {
            uint32_t current = callstack.top();
            total_children[current] = 0;
            if(children[current].empty())
            {
                callstack.pop();
                continue;
            }
            else
            {
                bool all_done = true;
                for(uint32_t i = 0; i < children[current].size(); i++)
                {
                    if(not done[children[current][i]])
                    {
                        all_done = false;
                        done[children[current][i]] = true;
                        callstack.push(children[current][i]);
                    }
                }
                if(all_done)
                {
                    for(uint32_t i = 0; i < children[current].size(); i++)
                    {
                        total_children[current] += total_children[children[current][i]] + 1;
                    }
                    callstack.pop();
                }
            }
        }


    after:
        printf("%u\n", total_children[cparent] + 1); // include self (+1)
    }
}
