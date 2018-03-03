#include <bits/stdc++.h>

using namespace std;

bool is_digit(char c)
{
    return '0' <= c and c <= '9';
}
bool is_letter(char c)
{
    return ('a' <= c and c <= 'z') or ('A' <= c and c <= 'Z');
}
char lower(char c)
{
    if('A' <= c and c <= 'Z')
        c += 32;
    return c;
}
bool is_palindrome(string& c)
{
    if(c.empty()) return false;
    for(uint32_t i = 0, j = c.size() - 1; i < j; i++, j--)
    {
        if(lower(c[i]) != lower(c[j]))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static array<uint32_t, 5> O, R;
    for(uint32_t i = 0; i < n; i++)
        cin >> O[i], O[i]--;
    string S;
    cin.ignore(); getline(cin, S);
    R[0] = count(S.begin(), S.end(), ' ');
    bool last_was_digit = false, last_was_letter = false, last_was_dot = false, word_since_dot = false;
    string buffer;
    for(char c : S)
    {
        if(is_digit(c))
        {
            if(not last_was_digit)
                last_was_digit = true, R[1]++;
        }
        else
            last_was_digit = false;
        if(is_letter(c))
        {
            if(not last_was_letter)
                last_was_letter = true, R[2]++;
            buffer.push_back(c);
        }
        else
        {
            if(last_was_letter)
            {
                word_since_dot = true;
                last_was_letter = false;
            }
            if(not buffer.empty())
            {
                R[4] += is_palindrome(buffer);
                buffer.clear();
            }
        }
        if(c == '.')
        {
            if(not last_was_dot and word_since_dot)
                last_was_dot = true, R[3]++, word_since_dot = false;
        }
        else
            last_was_dot = false;

    }
    R[4] += is_palindrome(buffer);
    for(uint32_t i = 0; i < n; i++)
        cout << R[O[i]] << " ";
}
