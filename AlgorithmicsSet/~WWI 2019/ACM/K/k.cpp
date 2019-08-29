#include <bits/stdc++.h>

using namespace std;

long long t[1000007];

int main()
{
    long long xd,xd2,res=0;
    int p,k,p1;
    size_t n;
    cin >> n;

    for(int i=1; i<=n; i++) cin>>t[i];

    xd=xd2=p=k=0;
    p1=1;

    for(int i=1; i<=n; i++){
        xd2+=t[i];
        if(xd2>0){
            xd2=0;
            p1=i+1;
        }
        if(xd2<xd){
            xd=xd2;
            k=i;
            p=p1;
        }
    }

    res+=xd;

    cout<<"p="<<p<<" k="<<k<<" xd="<<xd<<'\n';

    xd=xd2=0;
    for(int i=1; i<p; i++){
        xd2+=t[i];
        if(xd2<0) xd2=0;
        xd=max(xd,xd2);
    }

    xd2=0;
    for(int i=k+1; i<=n; i++){
        xd2+=t[i];
        if(xd2<0) xd2=0;
        xd=max(xd,xd2);
    }

    cout<<"xd="<<xd<<'\n';


    res+=xd;

    cout<<res;
}
