#include <algorithm>
#include <cstddef>
#include <vector>

using std::size_t;
using std::vector;
using std::__lg;

template<typename Value, typename Tag, typename ValueMonoid, typename TagMonoid, typename ApplyMonoid>
struct lazy_segment_tree
{
    size_t w;
    const Value identity;
    vector<Value> values;
    const Tag tag_identity;
    vector<Tag> tags;
    ValueMonoid f;
    TagMonoid g;
    ApplyMonoid a;

    lazy_segment_tree(size_t n, Value vid, Tag tid, ValueMonoid _f, TagMonoid _g, ApplyMonoid _a) :
        w(1 << __lg(2*n - 1)), identity(vid), values(2*w, vid),
        tag_identity(tid), tags(2*w, tid), f(_f), g(_g), a(_a) {}

    void touch(size_t i, size_t l, size_t r)
    {
        if(tags[i] != tag_identity)
        {
            if(l+1 < r)
            {
                for(auto j : {2*i, 2*i+1})
                    tags[j] = g(tags[j], tags[i]);
                auto m = (l + r) / 2;
                values[2*i+0] = a(values[2*i+0], tags[i], l, m);
                values[2*i+1] = a(values[2*i+1], tags[i], m, r);
            }
            tags[i] = tag_identity;
        }
    }

    Value get(size_t i, size_t nodeL, size_t nodeR, size_t getL, size_t getR, Tag tag)
    {
        if(getR <= nodeL or nodeR <= getL)
            return identity;
        else if(getL <= nodeL and nodeR <= getR)
        {
            if(tag != tag_identity)
                values[i] = a(values[i], tag, nodeL, nodeR), tags[i] = g(tags[i], tag);
            return values[i];
        }
        else
        {
            touch(i, nodeL, nodeR);
            const size_t nodeM = (nodeL + nodeR) / 2;
            auto r = f(
                get(2*i+0, nodeL, nodeM, getL, getR, tag),
                get(2*i+1, nodeM, nodeR, getL, getR, tag)
            );
            if(tag != tag_identity)
                values[i] = f(values[2*i], values[2*i + 1]);
            return r;
        }
    }

    Value put(size_t l, size_t r, Tag tag) { return l < r ? get(1, 0, w, l, r, tag) : identity; }
    Value get(size_t l, size_t r) { return put(l, r, tag_identity); }
    Value get() const { return values[1]; }
};
