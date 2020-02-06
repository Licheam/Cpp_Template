#include <cstdio>
#define MAXN 100005

int root,len;

struct node{
	int v,fa,ch[2],size,cnt;
}sp[MAXN];

void pushup(int x){
	sp[x].size=sp[sp[x].ch[0]].size+sp[sp[x].ch[1]].size+sp[x].cnt;
}

void rotate(int x){
	int f=sp[x].fa;
	int ff=sp[f].fa;
	int t=(sp[f].ch[1]==x);
	if(ff) sp[ff].ch[(sp[ff].ch[1]==f)]=x;
	sp[x].fa=ff;

	if(sp[x].ch[t^1]) sp[sp[x].ch[t^1]].fa=f;
	sp[f].ch[t]=sp[x].ch[t^1];

	sp[x].ch[t^1]=f; sp[f].fa=x;
	pushup(f); pushup(x);
}

void splay(int x,int goal=0){
	while(sp[x].fa!=goal){
		int f=sp[x].fa;
		int ff=sp[f].fa;
		if(ff!=goal){
			if((sp[f].ch[0]==x)==(sp[ff].ch[0]==f)) rotate(f);
			else rotate(x);
		}
		rotate(x);
	}
	if(!goal)
		root=x;
}

void insert(int x){
	int cur=root,f=0;
	while(cur&&sp[cur].v!=x){
		f=cur;
		cur=sp[cur].ch[x>sp[cur].v];
	}
	if(cur)
		sp[cur].cnt++;
	else{
		cur=++len;
		if(f) sp[f].ch[x>sp[f].v]=cur;
		sp[cur].ch[0]=sp[cur].ch[1]=0;
		sp[cur].fa=f;
		sp[cur].v=x;
		sp[cur].cnt=sp[cur].size=1;
	}
	splay(cur);
}

void find(int x){
	if(!root) return;
	int cur=root;
	while(x!=sp[cur].v && sp[cur].ch[x>sp[cur].v])
		cur=sp[cur].ch[x>sp[cur].v];
	splay(cur);
}

int kth(int x){
	if(!root || sp[root].size<x) return 0;
	int cur=root;
	while(1){
		if(x<=sp[sp[cur].ch[0]].size)
			cur=sp[cur].ch[0];
		else if(x>sp[sp[cur].ch[0]].size+sp[cur].cnt){
			x-=sp[sp[cur].ch[0]].size+sp[cur].cnt;
			cur=sp[cur].ch[1];
		}
		else return sp[cur].v;
	}
}

int pre(int x){
	find(x);
	if(x>sp[root].v) return root;
	int cur=sp[root].ch[0];
	while(sp[cur].ch[1])
		cur=sp[cur].ch[1];
	return cur;
}

int succ(int x){
	find(x);
	if(x<sp[root].v) return root;
	int cur=sp[root].ch[1];
	while(sp[cur].ch[0])
		cur=sp[cur].ch[0];
	return cur;
}

void erase(int x){
	int last=pre(x),next=succ(x),del;
	if(!last||!next){
		del=root;
	}
	else{
		splay(last);splay(next,last);
		del=sp[next].ch[0];
	}

	if(sp[del].cnt>1){
		sp[del].cnt--;
		splay(del);
	}
	else{
		if(del==root){
			root=sp[del].ch[(sp[del].ch[0]==0)];
			sp[sp[del].ch[(sp[del].ch[0]==0)]].fa=0;
		}
		else sp[next].ch[0]=0;

		// sp[del]=sp[len];
		// int f=sp[del].fa;
		// if(f) sp[f].ch[(sp[f].ch[1]==len)]=del;
		// if(sp[del].ch[0]) sp[sp[del].ch[0]].fa=del;
		// if(sp[del].ch[1]) sp[sp[del].ch[1]].fa=del;
		// len--;

	}
}


int n;
int main(){
	scanf("%d", &n);
	root=0;len=0;
	sp[0].fa=sp[0].ch[0]=sp[0].ch[1]=0;
	sp[0].cnt=sp[0].size=0;
	for(int i=1;i<=n;i++){
		int opt,x;
		scanf("%d %d", &opt, &x);
		if(opt==1){
			insert(x);
		}
		else if(opt==2){
			erase(x);
		}
		else if(opt==3){
			find(x);
			printf("%d\n", sp[sp[root].ch[0]].size+1);
		}
		else if(opt==4){
			printf("%d\n", kth(x));
		}
		else if(opt==5){
			printf("%d\n", sp[pre(x)].v);
		}
		else{
			printf("%d\n", sp[succ(x)].v);
		}
	}
	return 0;
}