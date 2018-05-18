#include <bits/stdc++.h>
using namespace std;

int main()
{
    double a,b,c;
	cout << fixed << setprecision(2);
	while(true){
		cin>>a>>b>>c;
		if(a!=0 or b!=0 or c!=0){
			cout<<a*b/c<<'\n';
		}
		else{
			break;
		}
	}
	return 0;
}
