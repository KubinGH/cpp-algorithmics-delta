#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;
typedef pair<int32_t, int32_t> point_t;

bool point_t_rev_less(const point_t& a, const point_t& b)
{
    return a.second < b.second or (not a.second < b.second and a.first < b.first);
}

template<typename T>
void uprint(T o)
{
    cerr << o;
}

template<typename A, typename B>
void uprint(pair<A, B> p)
{
    cerr << "(" << p.first << ", " << p.second << ")";
}

template <typename T, template <typename, typename...> class V, typename... Args>
void uprint(V<T, Args...>& it)
{
    cerr << "{";
    for(T i : it)
        uprint(i), cerr << "; ";
    cerr << "}";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    map<int32_t, vector<int32_t> > V;
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t x, y;
        cin >> x >> y;
        V[x].push_back(y);
    }
    for(auto it = V.begin(); it != V.end(); it++)
        sort(it->second.begin(), it->second.end());
    uint32_t result = 0;
    for(auto it1 = V.begin(); it1 != V.end(); it1++)
    {
        vector<int32_t>* v1, *v2;
        int32_t x1 = it1->first;
        for(auto it2 = it1; it2 != V.end(); it2++)
        {
            if(it1 == it2) continue;
            int32_t x2 = it2->first;
            if(it1->second.size() > it2->second.size())
                v2 = &it1->second, v1 = &it2->second;
            else
                v1 = &it1->second, v2 = &it2->second;
            uint32_t pairs = 0;
            if(v1->size() > 40 and v2->size() > 40 and v2->size() / v1->size() >= 6)
            {
                auto itb = v2->begin();
                for(int32_t y1 : *v1)
                {
                    if(*(itb = lower_bound(itb, v2->end(), y1)) == y1)
                        pairs++;
                    if(itb == v2->end()) break;
                }
            }
            else
            {
                uint32_t i = 0, j = 0;
                while(i < v1->size() or j < v2->size())
                {
                    if(i < v1->size() and j < v2->size() and (*v1)[i] == (*v2)[j])
                        pairs++, i++, j++;
                    else if(j >= v2->size() or (i < v1->size() and (*v1)[i] < (*v2)[j]))
                        i++;
                    else
                        j++;
                }
            }
            result += pairs * (pairs - 1) / 2;
        }
    }
    cout << result;
}
