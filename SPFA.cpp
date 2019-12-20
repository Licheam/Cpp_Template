#include <cstdio>
#include <climits>
#include <queue>

#define MAXN 100005
#define MAXM 500005

using namespace std;

struct edge
{
	int v,to,next;
}e[MAXM];

int n,m,p,f,g,w,tot=0,head[MAXN],dist[MAXN],flag[MAXN];

void add(int x,int y,int z){
	e[++tot].v=z;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

void spfa(int x){
	queue <int> Q;

	for(int i=1;i<=n;i++){
		dist[i]=INT_MAX;
		flag[i]=0;
	}
	Q.push(x);
	flag[x]=1;
	dist[x]=0;
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		for(int q=head[u];q;q=e[q].next){
			if(dist[u]+e[q].v<dist[e[q].to]){
				dist[e[q].to]=dist[u]+e[q].v;
				if(!flag[e[q].to])
					Q.push(e[q].to);
			}
		}
	}
}

int main(){
	scanf("%d %d %d",&n,&m,&p);
	for(int i=1;i<=n;i++)
		head[i]=0;
	for(int i=1;i<=m;i++){
		scanf("%d %d %d", &f, &g, &w);
		add(f,g,w);
	}
	spfa(p);
	for(int i=1;i<=n;i++)
		printf("%d ", dist[i]);
	return 0;
}