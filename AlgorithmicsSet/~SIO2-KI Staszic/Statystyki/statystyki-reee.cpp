#include <string>
#include <regex>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const regex re_number("\\d+");
const regex re_word("[a-zA-z]+");

int main()
{
    uint32_t n;
    cin >> n;
    vector<uint32_t> a(n);
    for(uint32_t i = 0; i < n; i++) cin >> a[i], a[i]--;
    string S;
    cin.ignore(); getline(cin, S);

    uint32_t R[5] = {0, 0, 0, 0, 0};

    R[0] = count(S.begin(), S.end(), ' ');

    R[1] = distance(sregex_iterator(S.begin(), S.end(), re_number), sregex_iterator());

    vector<uint32_t> dots;
    for(uint32_t i = 0; i < S.size(); i++)
        if(S[i] == '.') dots.push_back(i);
    uint32_t d = 0;
    vector<bool> used_dot(dots.size(), 0);

    R[2] = distance(sregex_iterator(S.begin(), S.end(), re_word), sregex_iterator());
    for(auto it = sregex_iterator(S.begin(), S.end(), re_word); it != sregex_iterator(); it++)
    {
        while(d < dots.size() and dots[d] < it->position()) d++;
        if(d < dots.size() and not used_dot[d]) R[3]++, used_dot[d] = true;
        string word = it->str();
        for(uint32_t i = 0; i < word.size(); i++) word[i] = tolower(word[i]);
        if(equal(word.begin(), word.end(), word.rbegin()))
            R[4]++;
    }

    //cerr << R[0] << " " << R[1] << " " << R[2] << " " << R[3] << " " << R[4] << endl;
    for(uint32_t i = 0; i < n; i++)
        cout << R[a[i]] << " ";
}
