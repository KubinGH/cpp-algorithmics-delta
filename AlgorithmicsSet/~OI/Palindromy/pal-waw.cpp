#include<bits/stdc++.h>
using namespace std;

const int N=207;
string s,res="\n";
int mx[N],mn[N],pre0[N],pre1[N];

bool ok(int a,int b)
{
	for(int i=0;i<(b-a+1)>>1;i++)
	{
		if(s[a+i]!=s[b-i]) return 0;
	}
	return 1;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> s;
	int n=s.length(),a;

	if(n&1)
	{
		cout << "NIE\n";
		return 0;
	}

	for(int i=2;i<=n;i+=2)
	{
		mn[i]=N;
		mx[i]=-N;
	}
	for(int i=2;i<=n;i+=2)
	{
		for(int j=1;j<i;j+=2)
		{
			if(ok(j-1,i-1))
			{
				if(mn[j-1]+1<mn[i])
				{
					mn[i]=mn[j-1]+1;
					pre0[i]=j-1;
				}
				if(mx[j-1]+1>mx[i])
				{
					mx[i]=mx[j-1]+1;
					pre1[i]=j-1;
				}
			}
		}
	}

	if(mn[n]==N)
	{
		cout << "NIE\n";
		return 0;
	}

	a=n;
	while(1)
	{
		for(int i=a;i>pre1[a];i--) res+=s[i-1];
		if(!pre1[a]) break;
		res+=' ';
		a=pre1[a];
	}
	res+='\n';
	a=n;
	while(1)
	{
		for(int i=a;i>pre0[a];i--) res+=s[i-1];
		if(!pre0[a]) break;
		res+=' ';
		a=pre0[a];
	}

	reverse(res.begin(),res.end());
	cout << res;

	return 0;
}
