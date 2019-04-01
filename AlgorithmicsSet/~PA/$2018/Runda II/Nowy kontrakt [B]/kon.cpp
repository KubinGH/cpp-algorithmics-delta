#include <bits/stdc++.h>

using namespace std;

const uint32_t Tpow10[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
};
int32_t log10floor(uint32_t x)
{
    for(uint32_t i = 0; i < 10; i++)
        if(Tpow10[i] > x)
            return i-1;
    return 10;
}

struct leaf_num
{
    string head;
    uint32_t zeros, tail;
    uint32_t tail_log10floor;
    leaf_num(string x) : head(x), zeros(0), tail(0) { tail_log10floor = -1u; normalize(); }
    void clear()
    {
        head.clear(); zeros = 0; tail = 0; tail_log10floor = -1u;
    }
    void normalize()
    {
        if(zeros and head.empty())
            zeros = 0;
        if(tail and not zeros)
        {
            string o; o.reserve(10);
            while(tail)
                o += (tail%10) + '0', tail /= 10;
            tail_log10floor = log10floor(tail);
            reverse(o.begin(), o.end());
            head += o;
        }
        while(not head.empty() and head.back() == '0')
            zeros++, head.pop_back();
    }
    leaf_num& operator++ ()
    {
        uint32_t f = log10floor(tail+1);
        if(tail+1 == Tpow10[f])
        {
            if(zeros == 0)
            {
                char last = '9';
                while(not head.empty() and last == '9')
                {
                    tail += Tpow10[f] * ((last = head.back()) - '0');
                    head.pop_back(); f++;
                }
                f--;
            }
            else
                zeros--;
        }
        tail++; tail_log10floor = f;
        normalize();
        return *this;
    }
    leaf_num& operator<<= (uint32_t x)
    {
        if(tail == 0)
            zeros += x;
        else
            tail *= Tpow10[x], tail_log10floor += x;
        return *this;
    }
    bool is_zero() const { return tail == 0 and head.empty(); }
    uint32_t size() const
    {
        if(is_zero())
            return 1;
        return (tail_log10floor+1) + zeros + head.size();
    }
    uint32_t operator[] (uint32_t i) const
    {
        if(is_zero()) return 0;
        if(i < head.size())
            return head[i] - '0';
        i = size() - i - 1;
        if(i < tail_log10floor+1)
            return (tail % Tpow10[i+1]) / Tpow10[i];
        else
            i -= tail_log10floor+1;
        if(i < zeros)
            return 0;
        else
            i -= zeros;
        return head.rbegin()[i] - '0';
    }
    bool operator== (const leaf_num& o) const
    {
        return size() == o.size() and tail == o.tail and zeros == o.zeros and head == o.head;
    }
    bool operator< (const leaf_num& o) const
    {
        if(size() != o.size())
            return size() < o.size();
        for(uint32_t i = 0; i < min(head.size(), o.head.size()); i++)
            if(head[i] != o.head[i])
                return head[i] < o.head[i];
        if(head.size() != o.head.size())
            return head.size() < o.head.size();
        return tail < o.tail;
    }
    bool operator<= (const leaf_num& o) const
        { return operator==(o) or operator<(o); }
    bool operator> (const leaf_num& o) const
        { return not operator<=(o); }
};

bool prequal(const leaf_num& a, const leaf_num& b)
{
    uint32_t p = min(a.size(), b.size());
    for(uint32_t i = 0; i < p; i++)
        if(a[i] != b[i])
            return false;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    leaf_num last(""), curr("");
    last.head.reserve(32); curr.head.reserve(32);
    uint64_t result = 0;
    while(n --> 0)
    {
        curr.clear();
        cin >> curr.head;
        curr.normalize();
        uint32_t p = curr.size();
        if(curr > last)
            {}
        else if(curr == last)
            curr <<= 1;
        else
        {
            if(prequal(curr, last))
            {
                leaf_num tmp = last;
                ++tmp;
                if(prequal(curr, tmp))
                    curr = tmp;
            }
            curr <<= last.size() - curr.size();
            if(curr <= last)
                curr <<= 1;
        }
        result += curr.size() - p;
        last = curr;
    }
    cout << result;
}
