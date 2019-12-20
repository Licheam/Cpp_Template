#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAXN 10005
#define MAXM 100005

using namespace std;

const int inf = 1e9;

int n,m,s,t,tot,head[MAXN],lbl[MAXN],cur[MAXN];

struct edge{//残量网络 residual network
    int to,cf,next;//Cf:residual capacity
}e[(MAXM<<1)+1];

void add(int x,int y,int z){
    tot++;
    e[tot].cf=z;
    e[tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

bool label_vertex(){//反向BFS
    memset(lbl+1,0,n*sizeof(lbl[0]));
    queue<int> q;
    lbl[t]=1;
    q.push(t);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int p=head[u];p;p=e[p].next){
            int v=e[p].to;
            if(e[p^1].cf && !lbl[v]){//只搜反向边
                lbl[v]=lbl[u]+1;
                q.push(v);
                if(v==s) return true;
            }
        }
    }
    return lbl[s]!=0;
}

int multi_augment(int u,int lim){//DFS 多路增广
    if(u == t) return lim;//走完了
    
    int used=0;
    for(int& p=cur[u];p;p=e[p].next){
        int v=e[p].to;
        if(e[p].cf && lbl[v]==lbl[u]-1){
            int rest=multi_augment(v,min(lim-used,e[p].cf));
            used+=rest;
            e[p].cf-=rest;
            e[p^1].cf+=rest;
            if(used==lim) break;
        }
    }
    return used;
}

int dinic(){
    int flow=0;
    while(label_vertex()){//BFS 标记
        for(int i=1;i<=n;i++) cur[i]=head[i];//当前弧优化
        flow+=multi_augment(s,inf);//DFS 顺着标记找增广路
    }
    return flow;
}

int main(){
    scanf("%d %d %d %d", &n, &m, &s, &t);
    tot=1;
    memset(head+1,0,n*sizeof(head[0]));
    for(int i=1;i<=m;i++){
        int f,g,w;
        scanf("%d %d %d",&f,&g,&w);
        add(f,g,w);
        add(g,f,0);
    }
    printf("%d\n", dinic());
    return 0;
}
