#include <cstdio>
#include <cstring>
#define MAXN 1000005

int n,m,cnt,next[MAXN];
char s1[MAXN],s2[MAXN];

void kmp(){
	next[0]=-1;
	for(int i=1,k=-1;i<=m;i++){
		while(k!=-1 && s2[k]!=s2[i-1])
			k=next[k];
		next[i]=++k;
	}
	cnt=0;
	for(int i=1,k=0;i<=n;i++){
		while(k!=-1 && s2[k]!=s1[i-1])
			k=next[k];
		if(m==++k){
			cnt++;
			printf("%d\n", i-m+1);
		}
	}
}

int main(){
	scanf("%s %s", s1, s2);
	n=strlen(s1);
	m=strlen(s2);
	kmp();
	for(int i=1;i<=m;i++){
		printf("%d ", next[i]);
	}
	return 0;
}