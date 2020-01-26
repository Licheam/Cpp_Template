#include <cstdio>
#include <cstring>

#define MAXN 10000005
#define MAXP 700005

int n,m,num,cnt,prime[MAXP],npri[MAXN];

void eular_sieve(){
	cnt=0;
	memset(npri,0,(n+1)*sizeof(npri[0]));
	npri[0]=npri[1]=1;
	for(int i=2;i<=n;i++){
		if(!npri[i]) prime[++cnt]=i;
		for(int j=1;j<=cnt && i*prime[j]<=n;j++){
			npri[i*prime[j]]=1;
			if(!(i%prime[j])) break;
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);
	eular_sieve();
	for(int i=1;i<=m;i++){
		scanf("%d",&num);
		puts(npri[num]?"No":"Yes");
	}
}