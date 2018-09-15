#include <bits/stdc++.h>

using namespace std;

typedef enum {
	OK,
	RISOLTO,
	IMPOSSIBILE
} stato_t;

typedef struct {
	int domino1;
	int domino2;
} coppia_t;

stato_t correggi(int N, int altezze[], coppia_t* scambio)
{
    uint32_t n = N, *H = (uint32_t*)altezze;
    coppia_t *result = scambio;
    auto check = [&H, &n]() {
        uint32_t x = H[0] - 1;
        for(uint32_t i = 1; i < n; i++)
        {
            if(x == 0)
                return false;
            x = max(x - 1, H[i] - 1);
        }
        return true;
    };
    if(check()) return OK;
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = i+1; j < n; j++)
        {
            swap(H[i], H[j]);
            result->domino1 = i; result->domino2 = j;
            if(check()) return RISOLTO;
            swap(H[i], H[j]);
        }
    }
    return IMPOSSIBILE;
}
