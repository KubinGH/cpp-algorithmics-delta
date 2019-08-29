#include<bits/stdc++.h>
using namespace std;
bool grid[507][507];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    char c;
    int n,m,x,y,k,y1,x1;
    cin>>n>>m;


    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            cin>>c;
            if(c=='#') grid[i][j]=1;
        }
    }


    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
                if(grid[i][j]||i==1||(i!=n&&(j&1))) cout<<'#';
                else cout<<'.';
        }
        cout<<'\n';
    }

    cout<<'\n';

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
                if(grid[i][j]||i==n||(i!=1&&(!(j&1)))) cout<<'#';
                else cout<<'.';
        }
        cout<<'\n';
    }

}
