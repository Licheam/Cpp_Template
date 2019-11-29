#include <cstdio>
#define MAXN 1005
#define MAXM 1000005

struct node{
	int to,next;
}e[MAXM];

int n1,n2,m,head[MAXN],tot,dfn[MAXN],mat[MAXN];

void add(int x,int y){
	tot++;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

bool augment(int x,int stamp){
	for(int p=head[x];p;p=e[p].next){
		int u=e[p].to;
		if(dfn[u] == stamp)
			continue;
		dfn[u]=stamp;
		if(!mat[u] || augment(mat[u],stamp)){
			mat[u]=x;
			return true;
		}
	}
	return false;
}

int match(){
	int cnt=0;
	for(int i=1;i<=n2;i++){
		mat[i]=0;
		dfn[i]=0;
	}
	for(int i=1;i<=n1;i++){
		if(augment(i,i))
			cnt++;
	}
	return cnt;
}

int main(){
	scanf("%d %d %d", &n1,&n2,&m);
	tot=0;
	for(int i=1;i<=n1;i++)
		head[i]=0;
	for(int i=1;i<=m;i++){
		int f,g;
		scanf("%d %d", &f, &g);
		if(f>n1 || g>n2)
			continue;
		add(f,g);
	}
	printf("%d\n", match());
	return 0;
}