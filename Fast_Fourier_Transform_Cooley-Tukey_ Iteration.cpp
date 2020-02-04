#include <cstdio>
#include <algorithm>
#include <complex>
#define MAXN 2100005

using namespace std;

const double PI=acos(-1);
complex<double> omg[MAXN],iomg[MAXN];

void init(int n){
	for(int i=0;i<n;i++){
		omg[i]=polar(1.0,2.0*PI*i/n);
		iomg[i]=conj(omg[i]);
	}
}

void FFT(int n,complex<double>* P,complex<double>* w){
	for(int i=0,j=0;i<n;i++){
		if(i<j) swap(P[i],P[j]);
		for(int l=n>>1;(j^=l)<l;l>>=1);
	}
	
	for(int i=2,l;i<=n;i<<=1){
		l=i>>1;
		complex<double> t;
		for(int j=0;j<n;j+=i){
			for(int k=0;k<l;k++){
				t=P[j+l+k]*w[n/i*k];
				P[j+l+k]=P[j+k]-t;
				P[j+k]=P[j+k]+t;
			}
		}
	}
}

int n,m,lim;
complex<double> A[MAXN],B[MAXN];

int main(){
	scanf("%d %d", &n, &m);
	for(lim=1;lim<=n+m;lim<<=1);
	fill(A,A+lim,complex<double>(0.0,0.0));
	fill(B,B+lim,complex<double>(0.0,0.0));
	for(int i=0,t;i<n+1;i++){
		scanf("%d", &t);
		A[i]+=t;
	}
	for(int i=0,t;i<m+1;i++){
		scanf("%d", &t);
		B[i]+=t;
	}
	init(lim);
	FFT(lim,A,omg);
	FFT(lim,B,omg);
	for(int i=0;i<lim;i++)
		A[i]=A[i]*B[i];
	FFT(lim,A,iomg);
	for(int i=0;i<n+m+1;i++)
		printf("%d ", (int)(A[i].real()/lim+0.5));
	return 0;
}