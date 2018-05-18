#import<iostream>
int A[1<<18],h,w,x,y,i;main(){std::cin>>h>>w>>x;while(std::cin>>y>>x)A[h*y+x-h-1]=1;for(;i<h*w;i++)std::cout<<(i%h?"":"\n")<<(A[i]?'X':'.');}