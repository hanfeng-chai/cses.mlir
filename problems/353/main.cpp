#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;

struct Mat{ long long a,b,c,d; };
Mat mul(const Mat&X, const Mat&Y){
    return {
        (X.a*Y.a+X.b*Y.c)%MOD, (X.a*Y.b+X.b*Y.d)%MOD,
        (X.c*Y.a+X.d*Y.c)%MOD, (X.c*Y.b+X.d*Y.d)%MOD
    };
}
Mat matpow(Mat M, long long p){
    Mat R{1,0,0,1};
    while(p>0){ if(p&1) R=mul(R,M); M=mul(M,M); p>>=1; }
    return R;
}
// g(n,e) = # sequences b_1..b_n in [0,e] with max(b_i,b_{i+1})=e for all consecutive pairs
long long g(long long n, long long e){
    long long em = e%MOD;
    Mat M{1,1,em,0};
    Mat P = matpow(M, n-1);
    long long A1=1, B1=em;
    long long An=(P.a*A1+P.b*B1)%MOD;
    long long Bn=(P.c*A1+P.d*B1)%MOD;
    return (An+Bn)%MOD;
}

int main(){
    int t; scanf("%d",&t);
    while(t--){
        long long n,k; scanf("%lld %lld",&n,&k);
        long long ans=1;
        long long kk=k;
        for(long long p=2;p*p<=kk;p++){
            if(kk%p==0){
                int e=0;
                while(kk%p==0){ kk/=p; e++; }
                ans = ans * g(n,e) % MOD;
            }
        }
        if(kk>1) ans = ans * g(n,1) % MOD;
        printf("%lld\n", ans);
    }
}
