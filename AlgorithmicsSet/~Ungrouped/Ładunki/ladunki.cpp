#include <bits/stdc++.h>
#define range(N, I) for(I = 0; I < N; I++)
#define VALUE_CHAR(n) n == 1 ? 'A' : (n == 2 ? 'B' : (n == 3 ? 'C' : '?'))
#define COUNT 25

// Two affecting each other can't have the same value.

typedef unsigned short uint16_t;

using namespace std;

inline uint16_t first_false(bool* arr, uint16_t length)
{
    for(uint16_t i = 0; i < length; i++)
    {
        if(not arr[i]) return i;
    }
    return length;
}

int main()
{
    uint16_t ball_count, affect_count, i;
    scanf("%u %u", &ball_count, &affect_count);
    static bool affections[COUNT][COUNT];
    static uint16_t result[COUNT];
    fill(affections, affections + (COUNT * COUNT), false);
    fill(result, result + COUNT, 0);
    range(COUNT, i)
    {
        uint16_t first, second;
        scanf("%u %u", &first, &second);
        affections[first - 1][second - 1] = true;
        affections[second - 1][first - 1] = true;
    }
    static bool done[COUNT];
    fill(done, done + COUNT, false);
    while(true)
    {
        uint16_t current = first_false(done, COUNT);
        result[current] = 1;
        queue<uint16_t> todo;
        todo.push_back(current);
        done[current] = true;
        while(true)
        {
            current = todo.front();
            todo.pop_front();
            range(COUNT, i)
            {
                if(affections[current][i])
                {
                    todo.push_back(i);
                    done[i] = true;
                }
            }

        }

    }
}
