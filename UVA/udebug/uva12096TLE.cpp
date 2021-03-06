/*已AC,每次放入vector逐个比较费时间，改为map则可以*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 & Author: GYH
 & Created Time:  2014年12月20日 星期六 20时29分20秒
 & File Name: uva12096.cpp
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>

using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef map<string,int> MSI;
typedef map<int,int> MII;
typedef pair<int,int> PII;

#define F(i,a,b) for(int i=a;i<=b;i++)
#define Fd(i,a,b) for(int i=a;i>=b;i--)
#define C(a) cout<<a<<endl
#define SET(a,t) memset(a,t,sizeof(a))
#define SETS(ST) while(!ST.empty()) ST.pop();
#define DEBUG puts("OK")
#define PM(a,x,y) F(i,0,x){F(j,0,y) cout<<a[i][j]<<" ";cout<<endl;}

#define FRER freopen("test","r",stdin)
#define FREW freopen("1","w",stdout)

template <typename T>
bool cmp(T a,T b){return a>b;}

const int inf = 0x7fffffff;
const int _inf= 0x8fffffff;
const LL  INF = 1e18;
const double EPS = 1e-8;
const double pi = acos(-1.0);
//const int N=  ;//The Range of Description

/*
  on ne voit bien qu avec le coeur.l essentiel est invisible pour les yeux
                                                                          */
struct p{
	int sum;
    int ID;
	set<int> s;
	p(int sum=0,int ID=-1):sum(sum),ID(ID) {s.clear();}
};

stack<p> st;
vector<p> v;
set<int>::iterator it;

void init()
{
	SETS(st);
	v.clear();
}

bool eq(p p1,p p2)
{
	set<int>::iterator it;
	if(p1.s.size()!=p2.s.size()) return 0;
	for(it=p1.s.begin();it!=p1.s.end();++it)
		p2.s.insert(*it);
	if(p2.s.size()!=p1.s.size()) return 0;
	return 1;
}

void print()
{
	printf("%d\n",st.top().sum);
}

void insv(p &p1)
{
	vector<p>::iterator it;
	for(it=v.begin();it!=v.end();++it)
		if(eq(p1,*it))
		{
			p1.ID=it->ID;
			return;
		}
	p1.ID=v.size();
	v.push_back(p1);
}

void PUS()
{
	p p1;
    insv(p1);
	p1.s.clear();
	st.push(p1);
	vector<p>::iterator it;
	for(it=v.begin();it!=v.end();++it)
		if(p1.ID==it->ID) return;
}

void DUP()
{
	if(st.empty()) return;
    p p1=st.top();
  	st.push(p1);
}

void UNI()
{
	if(st.empty() || st.size()==1) return;
	p p1=st.top();st.pop();
	p p2=st.top();st.pop();
	for(it=p1.s.begin();it!=p1.s.end();++it)
		p2.s.insert(*it);
	insv(p2);
	p2.sum=p2.s.size();
	st.push(p2);
}

void INS()
{
	if(st.empty() || st.size()==1) return;
	p p1=st.top();st.pop();
	p p2=st.top();st.pop();
	if(p1.s.empty()||p2.s.empty()) p2.s.clear();
	for(it=p1.s.begin();it!=p1.s.end();++it)
		if(p2.s.find(*it)==p2.s.end()) p2.s.erase(*it);
	insv(p2);
	p2.sum=p2.s.size();
	st.push(p2);
}

void ADD()
{
	if(st.empty() || st.size()==1) return;
	p p1=st.top();st.pop();
	p p2=st.top();st.pop();
	p2.s.insert(p1.ID);
	insv(p2);
	p2.sum=p2.s.size();
	st.push(p2);
}

void solve()
{
	//DEBUG;
	int n;
	scanf("%d",&n);
	while(n--)
	{
		char ch[20];
		scanf("%s",ch);
		switch(ch[0])
		{
			case 'P':PUS();break;
			case 'D':DUP();break;
			case 'U':UNI();break;
			case 'I':INS();break;
			case 'A':ADD();break;
        }
		print();
	}
	printf("***\n");
}

int main()
{
	//FRER;
	int t;
	scanf("%d",&t);
	while(t--){
		init();
		solve();
	}
    return 0;
}



