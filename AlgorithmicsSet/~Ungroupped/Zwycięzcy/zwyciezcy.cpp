#include <bits/stdc++.h>
#define MAX_PLAYERS 27

using namespace std;

uint16_t points[MAX_PLAYERS];

bool points_compare_reverse(char a, char b)
{
    return points[a - 'A'] > points[b - 'A'];
}

int main()
{
    static char players[MAX_PLAYERS];
    uint16_t player_count;
    scanf("%u", &player_count);
    for(uint16_t i = 0; i < player_count; i++)
    {
        players[i] = 'A' + i;
        scanf("%u", points + i);
    }
    sort(players, players + player_count, points_compare_reverse);
    string chars;
    for(uint16_t i = 0; i < player_count; i++)
    {
        if(i > 0 and points[players[i] - 'A'] < points[players[i - 1] - 'A'])
            break;
        else
            chars.push_back(players[i]);
    }
    sort(chars.begin(), chars.end());
    printf(chars.data());
}
