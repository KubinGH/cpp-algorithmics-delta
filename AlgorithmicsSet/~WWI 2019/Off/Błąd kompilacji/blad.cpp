template <int h = 0, int... v>
struct T {
    enum {
#define b h*16
        e = T<
    h+1, v..., b + 0, b + 1, b + 2, b + 3, b + 4, b + 5, b + 6, b + 7,
    b + 8, b + 9, b + 10, b + 11, b + 12, b + 13, b + 14, b + 15>::v
    };
};

template<int... v>
struct T<int(400), v...> {
    enum {
        e = max(v...)
    };
};

T<> x;
