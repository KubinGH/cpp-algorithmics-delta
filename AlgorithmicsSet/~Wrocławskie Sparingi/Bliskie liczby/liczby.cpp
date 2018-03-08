#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    set<tuple<uint64_t, uint64_t, uint64_t>> diffs;
    set<uint64_t> numbers;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        char c; uint64_t x;
        cin >> c >> x;
        if(c == '+')
        {
            numbers.insert(x);
            set<uint64_t>::iterator before, after, current = numbers.find(x);
            if(numbers.size() == 1)
                ;
            else if(*numbers.begin() == x)
            {
                after = current; after++;
                diffs.insert(make_tuple(*after - *current, *current, *after));
            }
            else if(*numbers.rbegin() == x)
            {
                before = current; before--;
                diffs.insert(make_tuple(*current - *before, *before, *current));
            }
            else
            {
                after = current; after++;
                before = current; before--;
                diffs.erase(make_tuple(*after - *before, *before, *after));
                diffs.insert(make_tuple(*current - *before, *before, *current));
                diffs.insert(make_tuple(*after - *current, *current, *after));
            }
        }
        else if(c == '-')
        {
            set<uint64_t>::iterator before, after, current = numbers.find(x);
            if(numbers.size() == 1)
                diffs.clear();
            else if(*numbers.begin() == x)
            {
                after = current; after++;
                diffs.erase(make_tuple(*after - *current, *current, *after));
            }
            else if(*numbers.rbegin() == x)
            {
                before = current; before--;
                diffs.erase(make_tuple(*current - *before, *before, *current));
            }
            else
            {
                after = current; after++;
                before = current; before--;
                diffs.erase(make_tuple(*after - *current, *current, *after));
                diffs.erase(make_tuple(*current - *before, *before, *current));
                diffs.insert(make_tuple(*after - *before, *before, *after));
            }
            numbers.erase(current);
        }
        if(not diffs.empty())
            cout << get<0>(*diffs.begin()) << '\n';
        else
            cout << "NIE\n";
    }
}
