#include <cstdio>
#include <queue>
#include <climits>

#define LL long long
#define MAXN 100005
#define MAXM 500005

using namespace std;

struct edge
{
	int v,next,to;
}e[MAXM];

int n,m,p,f,g,w,tot=0,dist[MAXN],head[MAXN],flag[MAXN];//flag:是否visit

void add(int x, int y, int z){
	tot++;
	e[tot].v=z;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}


struct HeapNode
{
	int v,u;
	bool operator< (const HeapNode& a) const{
		return v > a.v;
	}
};

priority_queue<HeapNode> Q;//small root
int u,q;
LL tem;

void djikstra(int x){
	for(int i=1;i<=n;i++){
		dist[i]=INT_MAX;
		flag[i]=0;
	}
	dist[x]=0;
	Q.push((HeapNode){0,x});
	while(!Q.empty()){
		u=Q.top().u;
		Q.pop();
		if(flag[u])
			continue;
		flag[u]=1;
		for(int q=head[u];q;q=e[q].next){
			if(dist[u]+e[q].v<=dist[e[q].to]){
				dist[e[q].to]=dist[u]+e[q].v;
				Q.push((HeapNode){dist[e[q].to],e[q].to});
			}
		}
	}
}

int main(){
	scanf("%d %d %d", &n, &m, &p);
	for(int i=1;i<=n;i++)
		head[i]=0;
	for(int i=1;i<=m;i++){
		scanf("%d %d %d", &f, &g, &w);
		add(f,g,w);
	}
	djikstra(p);
	for(int i=1;i<=n;i++)
		printf("%d ", dist[i]);
	return 0;
}