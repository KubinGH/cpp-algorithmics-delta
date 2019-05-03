#include <bits/stdc++.h>
#define NAMEDTUPLE(_name, _T1, _T2, _N1, _N2)       \
struct _name : public pair<_T1, _T2>                \
{                                                   \
    _name(const _T1& _0, const _T2& _1) : pair<_T1, _T2>(_0, _1) {}     \
    _T1& _N1() { return this->first; }              \
    const _T1& _N1() const { return this->first; }  \
    _T2& _N2() { return this->second; }             \
    const _T2& _N2() const { return this->second; } \
}

using namespace std;


struct test_dt : public tuple<uint32_t, uint32_t, uint32_t>
{
    test_dt(uint32_t a, uint32_t b, uint32_t c) : tuple<uint32_t, uint32_t, uint32_t>(a, b, c) {};
    uint32_t& field1() { return get<0>(*this); }
    const uint32_t& field1() const { return get<0>(*this); }
};

NAMEDTUPLE(test_dt2, vector<int>, int, con, val);

int main()
{
    test_dt p(1, 2, 3);
    cout << p.field1() << endl;
    p.field1() = 4;
    cout << p.field1() << endl;
    test_dt2 q({1, 2}, 3);
    q.con().push_back(3);
    cout << q.con().back() + q.val() << endl;
}
