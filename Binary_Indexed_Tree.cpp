#include <cstdio>

#define _for(i,a,b) for(int i=(a);i<=(b);i++)
#define MAXN 500005

int n,m,bit[MAXN],opt,p,q;

/*
取二进制中最低位
*/
int lowbit(int x){
	return x&(-x);
}

void change(int x,int y){
	for(;x<=n;x+=lowbit(x))
		bit[x]+=y;
}

int sum(int x){
	int s=0;
	for(;x>0;x-=lowbit(x))
		s+=bit[x];
	return s;
}

int main(){
	scanf("%d %d", &n, &m);
	_for(i,1,n+1)
		bit[i]=0;
	q=0;
	_for(i,1,n){
		scanf("%d", &p);
		change(i,p-q);
		q=p;
	}
	_for(i,1,m){
		int le,ri;
		scanf("%d", &opt);
		if(opt==1){
			scanf("%d %d %d",&le,&ri,&p);
			change(le,p);
			change(ri+1,-p);
		}
		else{
			scanf("%d", &p);
			printf("%d\n", sum(p));
		}
	}
}

/*
单点修改 区间查询
int main(){
	scanf("%d %d", &n, &m);
	_for(i,1,n)
		bit[i]=0;
	_for(i,1,n){
		scanf("%d",&q);
		change(i,q);
	}
	_for(i,1,m){
		scanf("%d %d %d",&opt, &p,&q);
		if(opt==1)
			change(p,q);
		else
			printf("%d\n", sum(q)-sum(p-1));
	}
	return 0;
}
*/