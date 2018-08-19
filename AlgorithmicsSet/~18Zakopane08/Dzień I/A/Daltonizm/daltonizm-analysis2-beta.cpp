#include <iostream>
#include <fstream>

using namespace std;

const size_t MAX2 = 333;
const uint64_t MOD = 1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static uint64_t R[MAX2][2*MAX2][2*MAX2], A[MAX2];
    R[0][0][0] = 1;
    ofstream out("o.txt");
    for(uint32_t n = 0; n < 309; n++)
    {
        for(uint32_t a = 0; a < 618; a++)
          for(uint32_t b = 0; b < 618; b++)
        {
            R[n+1][a+1][b+2] += R[n][a][b];
            R[n+1][a+1][b+2] %= MOD;
            if(b >= 1)
            {
                R[n+1][max(int(a)-2, 0)][b-1] += R[n][a][b];
                R[n+1][max(int(a)-2, 0)][b-1] %= MOD;
            }
        }
        for(uint32_t b = 0; b < 309; b++)
            A[n] += R[n][0][b], A[n] %= MOD;
        cout << n << ": " << A[n] << endl;
        out << A[n] << "LLU, ";
    }
}
