#include <bits/stdc++.h>

using namespace std;

const char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t cases;
    cin >> cases;

    while(cases --> 0)
    {
        size_t h, w, k;
        cin >> h >> w >> k;

        vector<vector<bool>> point(h, vector<bool>(w));
        int s = 0;

        for(size_t y = 0; y < h; y++)
          for(size_t x = 0; x < w; x++)
        {
            char c;
            cin >> c;
            point[y][x] = (c == 'R');
            if(point[y][x])
                s++;
        }
        size_t X, Y, i;
        auto next_field = [&]() {
            auto x = (Y%2 ? X-1 : X+1);
            if(x >= w) Y++;
            else X = x;
        };

        vector<string> color(h, string(w, '?'));

        int c;
        for(X = Y = i = 0, c = (s+k-1)/k; Y < h; next_field())
        {
            if(point[Y][X])
                c--;
            color[Y][X] = alphabet[i];

            if(not c and i+1 < k)
            {
                i++;
                if(i < (size_t)s%k)
                    c = (s+k-1) / k;
                else
                    c = s / k;
            }
        }

        for(auto row : color)
            cout << row << '\n';
    }
}
