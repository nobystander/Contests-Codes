#include<cstdio>

const int maxn=2000+5;
double dp[maxn][maxn];

int main()
{
	int n,t;
	double p;
	scanf("%d %lf %d",&n,&p,&t);
	for(int i=1;i<=t;++i)
		for(int j=1;j<=n;++j)
			dp[i][j]=dp[i-1][j]*(1-p)+(1+dp[i-1][j-1])*p;	//dp[i][j]  前i秒有j个人的期望
	printf("%.8lf\n",dp[t][n]);
}
