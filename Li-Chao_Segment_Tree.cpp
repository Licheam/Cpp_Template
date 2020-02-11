#include <cstdio>
#include <algorithm>
#define eps 1e-12
#define N 50000
#define MAXN 50005
#define MAXT 200005

using namespace std;

struct line{
	double k,b;
	int l,r;
	line(){}
	line(double _k,double _b,int _l,int _r)
	:k(_k),b(_b),l(_l),r(_r){}
}sgt[MAXT];

double calc(line l,int x){return l.k*x+l.b;}
int cross(line l1,line l2){return (int)((l1.b-l2.b)/(l2.k-l1.k));}

void modify(int cur,int l,int r,line li){
	if(li.l<=l && r<=li.r){
		if(calc(li,l)-calc(sgt[cur],l)>eps && calc(li,r)-calc(sgt[cur],r)>eps)
			sgt[cur]=li;
		else if(calc(li,l)-calc(sgt[cur],l)>eps || calc(li,r)-calc(sgt[cur],r)>eps){
			int mid=(l+r)>>1;
			if(calc(li,mid)-calc(sgt[cur],mid)>eps)
				swap(li,sgt[cur]);
			if(cross(li,sgt[cur])-mid<-eps)
				modify(cur<<1,l,mid,li);
			else modify(cur<<1|1,mid+1,r,li);
		}
	}
	else{
		int mid=(l+r)>>1;
		if(li.l<=mid) modify(cur<<1,l,mid,li);
		if(mid<li.r) modify(cur<<1|1,mid+1,r,li);
	}
}

double query(int cur,int l,int r,int x){
	if(l==r) return calc(sgt[cur],x);
	else{
		int mid=(l+r)>>1;
		if(x<=mid) return max(calc(sgt[cur],x),query(cur<<1,l,mid,x));
		else return max(calc(sgt[cur],x),query(cur<<1|1,mid+1,r,x));
	}
}

void built(int cur,int l,int r){
	sgt[cur].k=sgt[cur].b=0;
	sgt[cur].l=1; sgt[cur].r=N;
	if(l<r){
		int mid=(l+r)>>1;
		built(cur<<1,l,mid);
		built(cur<<1|1,mid+1,r);
	}
}

int n;

int main(){
	scanf("%d", &n);
	built(1,1,N);
	for(int i=1;i<=n;i++){
		char opt[10];
		scanf("%s",opt);
		if(opt[0]=='P'){
			double s,p;
			scanf("%lf %lf", &s, &p);
			modify(1,1,N,line(p,s-p,1,N));
		}
		else{
			int x;
			scanf("%d", &x);
			printf("%d\n", (int)(query(1,1,N,x)/100));
		}
	}
	return 0;
}