#include <cstdio>

#define ll long long

ll a,b,n;

ll binpow(ll x,ll y,ll m){
	ll r=1%m;
	while(y){
		if(y&1)
			r=r*x%m;
		x=x*x%m;
		y>>=1;
	}
	return r;
}

int main(){
	scanf("%lld %lld %lld",&a,&b,&n);
	printf("%lld^%lld mod %lld=%lld\n",a,b,n,binpow(a,b,n));
	return 0;
}