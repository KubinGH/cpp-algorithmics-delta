// n^3*k
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef long double ld;
const int maxn = 1505;
ll n, k, res;

void maxy(ll &a, ll b){a = max(a, b);}

struct punkt{
    ll x;
    ll y;
} p[maxn];
vector < punkt > pom;

bool por1(punkt a, punkt b){
    if(a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

ll iloczyn(punkt a, punkt b, punkt baza){
    return ((a.x-baza.x)*(b.y-baza.y) - (a.y-baza.y)*(b.x-baza.x));
}

vector<punkt> otoczka(vector<punkt> v){
    if(v.size() <= 2) return v;
    vector<punkt> ot;
    ot.pb(v[0]);
    ot.pb(v[1]);

    for(int i=2; i<(int)v.size(); i++){
        while(ot.size() >=2 && iloczyn(ot[ot.size()-1], v[i], ot[ot.size()-2]) >= 0){
            ot.pop_back();
        }
        ot.pb(v[i]);
    }
    return ot;
}

vector < punkt > gora;
vector < punkt > dol;
vector < punkt > pom2;
int nast[maxn];


main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    for(int i=0; i<n; i++){
        cin >> p[i].x >> p[i].y;
        pom.pb(p[i]);
    }
    sort(pom.begin(), pom.end(), por1);
    gora = otoczka(pom);
    for(int i=pom.size()-1; i>=0; i--)
        pom2.pb(pom[i]);
    dol = otoczka(pom2);
    dol.pop_back(), gora.pop_back();
    for(punkt i: gora) dol.push_back(i);
    n = dol.size();
    if(n <= k){
        ll tres = 0;
        for(int i=0; i<n-1; i++){
            tres += dol[i].x*dol[i+1].y - dol[i].y*dol[i+1].x;
        }
        tres += dol.back().x*dol[0].y - dol.back().y*dol[0].x;
        cout << setprecision(1) << fixed << abs(double(tres)/2);
        return 0;
    }
    static ll dp[100][100][100];    // max pole figury konczacej sie na i-j, gdy wybrane jest juz
    memset(dp, 0, sizeof(dp));
    for(int i=0; i<n; i++) nast[i] = (i+1)%n;


    for(int l=1; l<=k-2; l++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                for(int u=i+1; u<j; u=nast[u]){
                    maxy(dp[i][j][l], max(dp[i][u][l-1], dp[u][j][l-1]) +abs(iloczyn(dol[i], dol[j], dol[u])));
                }
            }
        }
    }

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            maxy(res, dp[i][j][k-2]);
    cout << setprecision(1) << fixed << double(res)/2;
}
