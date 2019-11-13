#include <cstdio>
#define LL long long
#define MAXN 100005
#define MAXT MAXN<<2

struct node{
	int le,ri;
	LL sum,tag;
}sgt[MAXT];

int n,m;
LL a[MAXN];

void built(int cur,int l,int r){
	sgt[cur].le=l;
	sgt[cur].ri=r;
	sgt[cur].tag=0;
	if(l+1<r){
		int le=cur<<1,ri=le+1;
		built(le,l,(l+r)>>1);
		built(ri,(l+r)>>1,r);
		sgt[cur].sum=sgt[le].sum+sgt[ri].sum;
	}
	else
		sgt[cur].sum=a[l];
}

void update(int cur){
	int le=cur<<1,ri=le+1;
	sgt[le].sum+=sgt[cur].tag*(sgt[le].ri-sgt[le].le);
	sgt[le].tag+=sgt[cur].tag;
	sgt[ri].sum+=sgt[cur].tag*(sgt[ri].ri-sgt[ri].le);
	sgt[ri].tag+=sgt[cur].tag;
	sgt[cur].tag=0;

}

void plus(int cur,int l,int r,LL delta){
	if(l<=sgt[cur].le && sgt[cur].ri<=r){
		sgt[cur].sum+=delta*(sgt[cur].ri-sgt[cur].le);
		sgt[cur].tag+=delta;
	}
	else{
		int le=cur<<1,ri=le+1,mid=(sgt[cur].le+sgt[cur].ri)>>1;
		if(sgt[cur].tag)
			update(cur);
		if(l<mid)
			plus(le,l,r,delta);
		if(mid<r)
			plus(ri,l,r,delta);
		sgt[cur].sum=sgt[le].sum+sgt[ri].sum;
	}
}

LL query(int cur,int l,int r){
	if(l<=sgt[cur].le && sgt[cur].ri<=r)
		return sgt[cur].sum;
	else{
		int le=cur<<1,ri=le+1,mid=(sgt[cur].le+sgt[cur].ri)>>1;
		if(sgt[cur].tag)
			update(cur);
		LL sum=0;
		if(l<mid)
			sum+=query(le,l,r);
		if(mid<r)
			sum+=query(ri,l,r);
		return sum;
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	built(1,1,n+1);
	for(int i=1;i<=m;i++){
		int cmd,le,ri;
		scanf("%d",&cmd);
		if(cmd==1){
			LL k;
			scanf("%d %d %lld",&le,&ri,&k);
			plus(1,le,ri+1,k);
		}
		else{
			scanf("%d %d",&le,&ri);
			printf("%lld\n", query(1,le,ri+1));
		}
	}
	return 0;
}