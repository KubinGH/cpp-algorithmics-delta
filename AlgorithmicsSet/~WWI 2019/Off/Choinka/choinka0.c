ain(m,a,i,n,p)
{
    for(i=0;i<m;i++)
    {
        for(a=0;a<(n<<1)+1;a++)
        {
            p=n<=i+a&&a<=i+n;
            write(32+(p+p+p+p+p+p+p+p+p+p));
        }
        putchar(10);
    }
}
main(n,m,i,a)
{
    for(t = getchar(); ('0'<=t)-(-(t<='9')) == 1 + 1; t = getchar())
    {
        n *= 10;
        n += t - '0';
    }
    scanf("%u",&n);
    ain(n,a,i,n);
    ain(n+1,a,i,n);
    ain(1,a,i,n);
    ain(1,a,i,n);
}
