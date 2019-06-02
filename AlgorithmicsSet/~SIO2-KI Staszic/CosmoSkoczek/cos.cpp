#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 7;

struct vec2d { size_t x, y; };

enum tile { Empty, Hole, Bonus };
map<char, tile> tile_dict = {
    {'.', Empty}, {'D', Hole}, {'H', Bonus}
};

template<typename T>
T read() { T x; cin >> x; return x; }

template<typename T, size_t D>
struct vector_tag
{
    using type = vector<typename vector_tag<T, D - 1>::type>;
};

template<typename T>
struct vector_tag<T, 0>
{
    using type = T;
};

template<typename T>
vector<T> make_vector(size_t n)
{
    return vector<T>(n);
}

template<
    typename T, typename... Args,
    typename Result = typename vector_tag<T, sizeof...(Args) + 1>::type
>
Result make_vector(size_t n, Args... args)
{
    return Result(n, make_vector<T>(args...));
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t h, w, k, t;
    cin >> h >> w >> k >> t;
    k = min(k, min(h - 1, w - 1));
    vector<vec2d> moves(t);
    for(size_t i = 0; i < t; i++)
        cin >> moves[i].x >> moves[i].y;
    auto tiles = make_vector<tile>(h, w);
    auto sg = make_vector<size_t>(h, w, k);
    auto sg_src = make_vector<bitset<MAX>>(h, w, k);
    for(size_t y = 0; y < h; y++)
      for(size_t x = 0; x < w; x++)
    {
        tiles[y][x] = tile_dict[read<char>()];
        for(size_t g = 0; g < k; g++)
        {
            auto& src = sg_src[y][x][g];
            for(auto v : moves)
            {
                if(x < v.x or y < v.y)
                    continue;
                size_t x1 = x-v.x, y1 = y-v.y;
                if(tiles[y1][x1] == Empty)
                    src.set(sg[y1][x1][g]);
                else if(tiles[y1][x1] == Hole and g+1 < k)
                    src.set(sg[y1][x1][g+1]);
                else if(tiles[y1][x1] == Bonus)
                {
                    src |= sg_src[y1][x1][g];
                    src.set(sg[y1][x1][g]);
                }
            }
            for(size_t& mex = sg[y][x][g]; mex < MAX; mex++)
                if(not src[mex])
                    break;
        }
    }
    size_t y, x;
    while(cin >> y >> x)
        cout << (sg[--y][--x][0] ? "TAK\n" : "NIE\n");
}
