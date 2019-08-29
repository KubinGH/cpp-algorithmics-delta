#include <bits/stdc++.h>

using namespace std;

const size_t total = 100, slaves = 5, random_seed = 1337, base_stage = 256;

pair<int, int> stage_data(int day)
{
    int start = 0, len = base_stage;
    while(start + len*2 <= day)
    {
        start += len*2;
        len *= 2;
    }
    return {start, len};
}

struct prisoner
{
    vector<size_t> reorder;
    mt19937 gen;

    int last_visit = -1;
    int master_counter = 0;
    int slave_counter = 0;

    prisoner()
    {
        gen.seed(random_seed);
        reorder.resize(100);
        iota(reorder.begin(), reorder.end(), 0);
        shuffle(reorder.begin(), reorder.end(), gen);
    }

    int turn(size_t i, int day, bool light)
    {
        i = reorder[i];

        auto stage = stage_data(day);
        int start, length;
        tie(start, length) = stage;

        bool first_stage_visit = false;

        if(last_visit == -1 or stage_data(last_visit).first != start)
        {
            first_stage_visit = true;
            master_counter = 0;
            slave_counter = 1;
        }

        bool part = (day >= start + length);

        // if part 1 just begun, information must be cleared
        if(day == start or day == start + length)
            return 0;

        if(i == 0) // master
        {
            if(not part)
            {
                if(not light and first_stage_visit)
                {
                    last_visit = day;
                    return 1;
                }
            }
            if(part)
            {
                if(light)
                {
                    //cout << master_counter << "/" << slaves << "!" << endl;
                    master_counter++;
                    if(master_counter == slaves)
                        return 2;
                    return 0;
                }
            }
        }
        else if(i <= slaves) // slaves
        {
            // if part 0 of stage, count exactly $total / slaves$ and then stop
            // in part 1, if counted $total / slaves$, report information to master
            last_visit = day;
            if(not part)
            {
                if(light and slave_counter < int(total / slaves))
                {
                    slave_counter++;
                    //cout << slave_counter << "/" << total / slaves << endl;
                    return 0;
                }
            }
            else if(part)
            {
                //cout << "?? " << (not light) << " " << total/slaves << endl;
                if(not light and (slave_counter == total / slaves))
                {
                    slave_counter = 1;
                    //cout << "slave " << i << "$" << endl;
                    return 1;
                }
            }
        }
        else // subhuman
        {
            // if light is already on, communication must remain
            // if haven't visited in this stage yet and it is okay, turn light on
            if(not part)
            {
                if(not light and first_stage_visit)
                {
                    last_visit = day;
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
