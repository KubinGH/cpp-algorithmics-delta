#include <bits/stdc++.h>
#define P(u,v) A[(*u-1)*n+*v-1]
#define R(p) scanf("%d",&p);
int n,k,q,A[1<<22],V[2048],*s=V;int main(){R(n)while(q<n*n)R(A[q++])R(q)while(q--){R(k)while(k--){R(*s)if(P(V,s))std::swap(*V,*s);s++;}while(--s>V)k&=!P(V,s)&&P(s,V);printf("%d\n",k&1?*V:-1);}}