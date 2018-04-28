#include <bits/stdc++.h>
#ifdef _WIN32
#define LLU_FMT "%I64u"
#else
#define LLU_FMT "%llu"
#endif

using namespace std;

typedef unsigned long long int uint64_t;
typedef unsigned int uint32_t;
typedef pair<uint64_t, uint32_t> ipair;
typedef set<ipair> pair_set;

const size_t MAX = 5e5;

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static uint64_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        scanf(LLU_FMT, A+i);
    static uint32_t L[MAX], R[MAX];
    fill(L, L + n, -1u);
    fill(R, R + n, n);
    deque<ipair> Q;
    for(uint32_t i = n; i --> 0;)
    {
        bool a = false;
        while(not Q.empty() and Q.begin()->first <= A[i])
        {
            if(Q.begin()->first == A[i] and Q.begin()->second > i)
            {
                Q.push_front(make_pair(A[i], i));
                a = true;
                break;
            }
            L[Q.begin()->second] = i;
            Q.pop_front();
        }
        if(not a) Q.push_front(make_pair(A[i], i));
    }
    Q.clear();
    for(uint32_t i = 0; i < n; i++)
    {
        bool a = false;
        while(not Q.empty() and Q.begin()->first <= A[i])
        {
            if(Q.begin()->first == A[i] and Q.begin()->second > i)
            {
                Q.push_front(make_pair(A[i], i));
                a = true;
                break;
            }
            R[Q.begin()->second] = i;
            Q.pop_front();
        }
        if(not a) Q.push_front(make_pair(A[i], i));
    }
    uint64_t r = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        //cout << i << ": " << (int)L[i] << " " << (int)R[i] << endl;
        r += uint64_t(i - L[i]) * uint64_t(R[i] - i) * A[i];
    }
    printf(LLU_FMT, r);
}

