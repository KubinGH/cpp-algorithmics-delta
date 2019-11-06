#include <iostream>
#include <vector>
#include <ktl/geometry/vec2d.cpp>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    using u64 = uint64_t;

    size_t n;
    cin >> n;

    vector<vec2d> vertices(n);
    for(auto& V : vertices)
        cin >> V.x >> V.y;

    size_t q;
    cin >> q;

    while(q --> 0)
    {
        vec2d P;
        cin >> P.x >> P.y;

        bool ok = false;
        for(size_t i = 1; i+1 < n; i++)
        {
            vec2d A = vertices[0], B = vertices[i], C = vertices[i+1];
            if(abs(area(A, B, P)) + abs(area(B, C, P)) + abs(area(C, A, P)) == -area(A, B, C))
                ok = true;
        }
        if(not ok)
        {
            cout << '0' << endl;
            continue;
        }

        int64_t result = 0;
        for(size_t a = 0, b = 1; a < n; a++)
        {
            #define A vertices[a]
            #define B vertices[b]
            if(b == a) b++;
            while(b < n and ((P - A) ^ (B - P)) > 0)
                b++;
            b--;

            result += (u64)b*(b+1)/2 - (u64)a*(a+1)/2 - u64(b-a)*(a+1);
            result += u64(n-b-1)*(n+a-1) - (u64)n*(n-1)/2 + (u64)b*(b+1)/2;
            #undef A
            #undef B
        }

        result = -result;
        for(size_t i = 0; i+2 < n; i++)
            result += u64(n-i-1)*(n-i-2)/2;

        cout << result << endl;
    }
}
