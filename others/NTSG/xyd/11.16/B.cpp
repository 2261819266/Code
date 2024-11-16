#include<bits/stdc++.h>
using namespace std;
int n,x,a[1005],ans=1001,s=0;
bool b[1005];
void dfs(int sum,int t)
{
	if(t==ans) return;
	if(sum%x==0)
	{
		ans=t;
		return;
	}
	int qwq=a[lower_bound(a,a+n,sum%x)-a];
	ans=min(ans,t+x-(sum%x));
	dfs(sum-qwq,t+1);
}
int main()
{
 	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	memset(b,0,sizeof(b));
 	cin>>n>>x;
 	for(int i=0;i<n;i++)
 	{
 		cin>>a[i];
 		s+=a[i];
	}
	sort(a,a+n);
	dfs(s,0);
	cout<<ans<<endl;
 	return 0;
}