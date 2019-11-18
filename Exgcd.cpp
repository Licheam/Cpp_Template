#include <cstdio>

int exgcd(int a,int b,int& x,int& y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	int g=exgcd(b,a%b,x,y);
	int t=x;
	x=y;
	y=t-(a/b)*y;
	return g;
}

int main(){
	int a,b,x,y;
	scanf("%d %d",&a,&b);
	int g=exgcd(a,b,x,y);
	g=b/g;
	printf("%d\n", (x%g+g)%g);
	return 0;
}