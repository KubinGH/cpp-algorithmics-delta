#import<iostream>
int A[1<<18],h,w,x,y,i,k;using namespace std;main(){cin>>h>>w>>k;while(k--)cin>>y>>x,A[h*y+x-h-1]=1;for(;i<h*w;i++)cout<<(i%h?"":"\n")<<(A[i]?'X':'.');}