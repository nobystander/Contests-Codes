#include<bits/stdc++.h>
using namespace std;

const int maxn=100000+10;
int save[maxn],rem[maxn]; 

int main()
{
	//freopen("./test.txt","r",stdin);
	int T,m,k;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&m,&k);
		for(int i=1;i<=k;++i){
			scanf("%d",save+i);
		}
		memset(rem,0,sizeof(rem));
		int person[maxn],mood[maxn];
		int dec=0,first=0;
		for(int i=1;i<m;++i){
			scanf("%d %d",&person[i],&mood[i]);
			if(!first && mood[i]) first=i;
			if(first && person[i]) rem[person[i]]=1;
		}
		for(int j=1;j<m;++j){
			if(j==first){
				int res=dec;
				for(int i=1;i<=k;++i) if(!rem[i] && save[i]<=dec){
					res=min(save[i],res);
					save[i]=0;
				}
				dec-=res;
				if(!person[j]) ++dec;
				else --save[person[j]];
				continue;
			}
			if(person[j])
				--save[person[j]];
			else
				++dec;
		}

		for(int i=1;i<=k;++i)
			if(save[i]-dec>0) putchar('N');
			else putchar('Y');
		putchar('\n');
	}

	return 0;
}
