#include <cstdio>
#include <algorithm>
#include <complex>
#define MAXN 4000005

using namespace std;

complex<double> omega[MAXN],arti_omega[MAXN],temp[MAXN];

void init_omega(int n){
	double PI=acos(-1);
	for(int i=0;i<n;i++){
		omega[i]=complex<double>(cos(2*PI*i/n),sin(2*PI*i/n));
		arti_omega[i]=conj(omega[i]);
	}
}

void FFT(int n,complex<double>* buffer,int offset,int step,complex<double>* omega){
	if(n==1) return;
	int m=n>>1;
	FFT(m,buffer,offset,step<<1,omega);
	FFT(m,buffer,offset+step,step<<1,omega);
	for(int i=0;i<m;i++){
		int pos=2*i*step;
		temp[i]=buffer[offset+pos]+omega[i*step]*buffer[offset+step+pos];
		temp[i+m]=buffer[offset+pos]-omega[i*step]*buffer[offset+step+pos];
	}
	for(int i=0;i<n;i++)
		buffer[offset+i*step]=temp[i];
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
	init_omega(lim);
	FFT(lim,A,0,1,omega);
	FFT(lim,B,0,1,omega);
	for(int i=0;i<lim;i++)
		A[i]=A[i]*B[i];
	FFT(lim,A,0,1,arti_omega);
	for(int i=0;i<n+m+1;i++)
		printf("%d ", (int)(A[i].real()/lim+0.5));
	return 0;
}