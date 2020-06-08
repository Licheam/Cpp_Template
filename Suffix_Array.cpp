#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1000005
using namespace std;

//sa:排名对应的前缀, rk:前缀的排名, tp:上次的rk, tax:排名对应的个数
//height:排名i与i-1后缀的LCP(最长公共前缀)
int sa[MAXN],rk[MAXN],tp[MAXN],tax[MAXN],height[MAXN];
char s[MAXN];

void rsort(int n,int m){
	memset(tax,0,(m+1)*sizeof(tax[0]));
	for(int i=1;i<=n;i++) tax[rk[i]]++;
	for(int i=1;i<=m;i++) tax[i]+=tax[i-1];
	for(int i=n;i>=1;i--) sa[tax[rk[tp[i]]]--]=tp[i];
}

void get_sa(char* s){
	int n=strlen(s+1), m=0;
	for(int i=1;i<=n;i++)
		m=max(m,rk[i]=s[i]),tp[i]=i;
	rsort(n,m);
	for(int k=1,p;p<n;k<<=1,m=p){
		p=0;
		for(int i=n-k+1;i<=n;i++) tp[++p]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) tp[++p]=sa[i]-k;
		rsort(n,m);
		swap(tp,rk);
		rk[sa[1]]=p=1;
		for(int i=2;i<=n;i++)
			rk[sa[i]]=(tp[sa[i]]==tp[sa[i-1]] && tp[sa[i]+k]==tp[sa[i-1]+k])?p:++p;
	}

	//利用height[i+1]>=height[i]-1
	for(int i=1,k=0;i<=n;i++){
		if(k) k--;
		while(rk[i]>1 && s[i+k]==s[sa[rk[i]-1]]+k) k++;
		height[rk[i]]=k;
	}
}

int main(){
	scanf("%s",s+1);
	get_sa(s);
	for(int i=1;i<=n;i++)
		printf("%d ", sa[i]);
	return 0;
}