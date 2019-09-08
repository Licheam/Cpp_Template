#include <cstdio>

#define MAXN 10000005
#define MAXP 700000

#define _for(i,a,b) for(int i=(a);i<=(b);i++)

int n,m,num,cnt=0,prime[MAXP],ispri[MAXN];

void eular_sieve(){
	ispri[0]=ispri[1]=0;
	_for(i,2,n)
		ispri[i]=1;
	_for(i,2,n){
		if(ispri[i])
			prime[++cnt]=i;
		for(int j=1,t=i*prime[1]; j<=cnt&&t<=n; t=i*prime[++j]){
			ispri[t]=0;
			if(!(i%prime[j]))
				break;
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);
	eular_sieve();
	_for(i,1,m){
		scanf("%d",&num);
		puts(ispri[num]?"Yes":"No");
	}
}