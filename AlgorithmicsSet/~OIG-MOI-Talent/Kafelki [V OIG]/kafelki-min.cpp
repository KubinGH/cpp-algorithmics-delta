#import<cstdio>
char*s,S[256];main(){scanf("%s",s=S+1);while(*s)*s=*s++%48*3;s[-1]+=8;while(s-->S)s[-1]+=*s/10,*s=*s%10+48;puts(S+1-*S/49);}