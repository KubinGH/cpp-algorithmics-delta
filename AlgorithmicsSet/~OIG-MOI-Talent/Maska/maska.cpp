#import<bits/stdc++.h>
int a[3];
main()
{
    std::cin>>a[0]>>a[1]>>a[2];
    std::sort(a,a+3);
    std::cout<<a[1]/2;
}
