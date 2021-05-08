#include <bits/stdc++.h>

using namespace std;

using vec = complex<int64_t>;

const int64_t oo = INT64_MAX;

istream& operator>> (istream& in, vec& v)
{
    int64_t x, y;
    in >> x >> y;
    v = vec(x, y);
    return in;
}

template<typename It>
int64_t _min_distance(It first, It last)
{
    int64_t d = +oo;
    if(last - first <= 10)
    {
        for(auto it1 = first; it1 != last; ++it1)
            for(auto it2 = it1 + 1; it2 != last; ++it2)
                d = min(d, norm(*it2 - *it1));
    }
    else
    {
        auto mid = first + (last - first) / 2;
        auto d1 = _min_distance(first, mid), d2 = _min_distance(mid, last);
        d = min({d, d1, d2});
        int64_t ds = floor(sqrt(d));
        vector<vec> stripe;
        for(auto it = first; it != last; ++it)
            if(mid->real() - ds <= it->real() and it->real() <= mid->real() + ds)
                stripe.push_back(*it);
        sort(stripe.begin(), stripe.end(), [](vec a, vec b) {
            return pair(a.imag(), a.real()) < pair(b.imag(), b.real());
        });
        for(size_t i = 0; i < stripe.size(); i++)
        {
            auto j = i + 1;
            while(j < stripe.size() and stripe[j].imag() <= stripe[i].imag() + ds)
                d = min(d, norm(stripe[i] - stripe[j++]));
        }
    }
    return d;
}

int64_t min_distance(vector<vec> points)
{
    sort(points.begin(), points.end(), [](vec a, vec b) {
        return pair(a.real(), a.imag()) < pair(b.real(), b.imag());
    });
    return _min_distance(points.begin(), points.end());
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<vec> points(n);
    for(auto& p : points)
        cin >> p;

    cout << min_distance(points) << endl;
}
