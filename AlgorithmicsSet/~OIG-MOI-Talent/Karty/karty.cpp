#include <bits/stdc++.h>

using namespace std;

const char* S[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "D", "K", "A"};

int main()
{
    string A, B;
    cin >> A >> B;
    if(A == B) { cout << "R"; return 0; };
    for(uint32_t i = 13; i --> 0; )
        if(S[i] == A) { cout << "A"; return 0; } else if(S[i] == B) { cout << "B"; return 0; }
}
