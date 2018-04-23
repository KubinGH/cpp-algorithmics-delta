#include <cstdio>
char*s,S[256];
main()
{
    scanf("%s",s=S+1);
    while(*s)
        *s-=48,*s++*=3;
    s[-1]+=8;
    while(s-->S)
        s[-1]+=*s/10,*s%=10,*s+=48;
    puts(S+(*S<49));
}
