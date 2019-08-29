#include <bits/stdc++.h>

using namespace std;

struct prisoner
{
    vector<int> visits;

    int counter = 0;
    bool counter_man = false;
    bool is_counted = true, used_light = false;

    int turn(int index, int day, bool light) {
        if(visits.size() < 3)
            visits.push_back(day);
        if(day < 99)
        {
            if(not light)
            {
                is_counted = false;
                if(not counter_man and visits.size() == 2)
                {
                    counter_man = true;
                    return 1;
                }
            }
        }
        else if(day == 99)
        {
            if(not light)
                return 2;
            return 0;
        }
        else
        {
            if(counter_man)
            {
                if(light)
                {
                    if(++counter == 100 - visits[1])
                        return 2;
                    return 0;
                }
            }
            else if(is_counted)
            {
                if(not light and not used_light)
                {
                    used_light = true;
                    return 1;
                }
            }
        }
        return light;
    }
} local;

int izolatka(int nr_wieznia, int nr_dnia, bool zarowka)
{
    return local.turn(nr_wieznia, nr_dnia, zarowka);
}


#ifdef XHOVA

int main()
{
    const size_t C = 10000;

    vector<size_t> order(C);
    iota(order.begin(), order.end(), 0);
    for(size_t i = 0; i < order.size(); i++)
        order[i] %= 100;
    shuffle(order.begin(), order.end(), mt19937{(size_t)time(0)});

    prisoner p[100];

    bitset<100> v;
    size_t day = 0;
    bool light = false;

    while(true)
    {
        size_t i = order[day % C];
//        size_t i = (day / 100000) % 100;
        v[i] = true;

        auto ret = p[i].turn(i, day, light);
        if(ret == 0)
            light = false;
        else if(ret == 1)
            light = true;
        else if(ret == 2)
        {
            assert(v.count() == 100);
            break;
        }
        else
            abort();

        day++;
    }
    cout << "Finished on day " << day << ". " << endl;
}


#endif
