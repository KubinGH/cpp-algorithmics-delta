// Li Chao Tree, as described in:
//  https://cp-algorithms.com/geometry/convex_hull_trick.html
// Data structure for inserting functions f(x) and finding the function
//  which is minimum at given x, under the assumption that each pair of
//  functions cross at most once in the range
// Dynamic allocation is used for easier adaptation for floating point types.
// Operations have O(log (R-L)/ε) complexity.
// Template:
//  Value is the type returned by functions
//  Arg is the function parameter type. Integral types have their range length
//   rounded up to the next power of 2, so that the tree works better
//   (each leaf manages a different range)
//  Fun is the function type, should implement operator() (Arg x), operator- (),
//   and default constructor returning f(x) = +oo (or -oo if negated)
// mirror_ox mirrors everything around the X axis internally, so that the
//  maximum is kept instead of minimum.

// Last revision: June 2019


#include <type_traits>
#include <algorithm>
#include <memory>
#include <limits>

using std::unique_ptr; using std::make_unique;
using std::swap; using std::__lg;
using std::numeric_limits;
using std::is_integral;

template<typename Value, typename Arg, typename Fun>
struct li_chao_tree
{
    const Arg rangeL, rangeR, eps;
    const bool mirror_ox;

    struct li_chao_node
    {
        Fun opt;
        unique_ptr<li_chao_node> left_child, right_child;
        li_chao_node* get_left_child()
        {
            if(not left_child)
                left_child = make_unique<li_chao_node>();
            return left_child.get();
        }
        li_chao_node* get_right_child()
        {
            if(not right_child)
                right_child = make_unique<li_chao_node>();
            return right_child.get();
        }
        void insert(Fun fun, Arg left, Arg right, Arg eps)
        {
            Arg mid = left + (right - left) / 2;
            bool opt_left = fun(left) < opt(left),
                 opt_mid = fun(mid) < opt(mid);
            if(opt_mid)
                swap(fun, opt);
            if(left + eps >= right)
                return;
            else if(opt_left != opt_mid)
                return get_left_child()->insert(fun, left, mid, eps);
            else
                return get_right_child()->insert(fun, mid, right, eps);
        }
        Fun get(Arg x, Arg left, Arg right, Arg eps)
        {
            Arg mid = left + (right - left) / 2;
            if(left + eps >= right)
                return opt;
            Fun lo;
            if(x < mid)
                lo = (left_child ? left_child->get(x, left, mid, eps) : Fun());
            else
                lo = (right_child ? right_child->get(x, mid, right, eps) : Fun());
            return lo(x) < opt(x) ? lo : opt;
        }
    } root;

    template<typename T = Arg, typename std::enable_if<not is_integral<T>::value, bool>::type = true>
    li_chao_tree(Arg _rangeL, Arg _rangeR, Arg _eps, bool _mirror_ox = false)
        : rangeL(_rangeL), rangeR(_rangeR), eps(_eps), mirror_ox(_mirror_ox) {}

    template<typename T = Arg, typename std::enable_if<is_integral<T>::value, bool>::type = true>
    li_chao_tree(Arg _rangeL, Arg _rangeR, bool _mirror_ox = false)
        : rangeL(_rangeL), rangeR(_rangeL + (1 << __lg(2*(_rangeR-_rangeL)-1))),
          eps(1), mirror_ox(_mirror_ox) {}

    void insert(Fun fun)
    {
        return root.insert(mirror_ox ? -fun : fun, rangeL, rangeR, eps);
    }
    Fun get(Arg x)
    {
        auto r = root.get(x, rangeL, rangeR, eps);
        return mirror_ox ? -r : r;
    }
    Value get_value(Arg x)
    {
        return get(x)(x);
    }
};

template<typename T>
struct li_chao_line
{
    T slope, constant;
    li_chao_line() : slope(0), constant(numeric_limits<T>::max()) {}
    li_chao_line(T a, T b) : slope(a), constant(b) {}
    T operator() (T x) const { return slope*x + constant; }
    li_chao_line operator- () const { return {-slope, -constant}; }
};

template<typename T, typename A = T>
using line_li_chao_tree = li_chao_tree<T, A, li_chao_line<A>>;
