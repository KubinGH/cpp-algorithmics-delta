#include <bits/stdc++.h>
#define MAX 2000
#define IS_VOWEL(X) (X == 'a' or X == 'e' or X == 'i' or X == 'o' or X == 'u' or X == 'y')

using namespace std;

typedef unsigned short uint16_t;

int main()
{
    static char verse1[MAX + 1], verse2[MAX + 1], line[MAX + 1];
    uint16_t n, k, result = 0, i, j, q, length1, length2, vowels1, vowels2;
    cin >> n >> k;
    cin.ignore();
    for(q = 0; q < n; q++)
    {
        gets(line);
        j = 0;
        for(i = 0; line[i] != '\0'; i++)
        {
            if(line[i] != ' ')
            {
                verse1[j] = line[i];
                j++;
            }
        }
        verse1[j] = '\0';
        length1 = j;
        gets(line);
        j = 0;
        for(i = 0; line[i] != '\0'; i++)
        {
            if(line[i] != ' ')
            {
                verse2[j] = line[i];
                j++;
            }
        }
        verse2[j] = '\0';
        length2 = j;
        if(length1 < k or length2 < k)
            goto after;
        vowels1 = 0;
        for(i = 0; i < length1; i++)
            if(IS_VOWEL(verse1[i])) vowels1++;
        vowels2 = 0;
        for(i = 0; i < length2; i++)
            if(IS_VOWEL(verse2[i])) vowels2++;
        if(vowels1 != vowels2)
            goto after;
        for(i = length1 - k, j = length2 - k; i < length1; i++, j++)
        {
            if(verse1[i] != verse2[j])
                goto after;
        }
        result++;
    after:;
    }
    printf("%u", result);
}
