#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
long long pw(long long a,long long b){a%=MOD;if(a<0)a+=MOD;long long r=1;while(b>0){if(b&1)r=r*a%MOD;a=a*a%MOD;b>>=1;}return r;}
int main(){
    int n; scanf("%d",&n);
    vector<long long> fact(n+1), inv(n+1);
    fact[0]=1; for(int i=1;i<=n;i++) fact[i]=fact[i-1]*i%MOD;
    inv[n]=pw(fact[n],MOD-2); for(int i=n;i>0;i--) inv[i-1]=inv[i]*i%MOD;
    auto C=[&](int a,int b)->long long{ if(b<0||b>a)return 0; return fact[a]*inv[b]%MOD*inv[a-b]%MOD; };
    // f(n,k) = sum_s C(n,s) * forest(n,s) * |stirling1(s,k)|
    //        = [y^k] sum_s w(s) * y(y+1)...(y+s-1),  w(s)=C(n,s)*forest(n,s)
    // forest(n,s) = (s==n)?1 : s * n^{n-s-1}
    vector<long long> w(n+1,0);
    for(int s=1;s<=n;s++){
        long long forest = (s==n)? 1 : (long long)s%MOD * pw(n, n-s-1)%MOD;
        w[s]=C(n,s)*forest%MOD;
    }
    vector<long long> p(n+2,0), R(n+2,0);
    p[0]=1; int deg=0;
    for(int s=1;s<=n;s++){
        // p *= (y + (s-1)) : p degree becomes s
        for(int d=deg+1; d>=1; d--) p[d]=(p[d-1] + (long long)(s-1)%MOD*p[d])%MOD;
        p[0]=(long long)(s-1)%MOD*p[0]%MOD;
        deg++;
        // R += w[s]*p
        for(int d=1; d<=deg; d++) R[d]=(R[d]+w[s]*p[d])%MOD;
    }
    string out; out.reserve(n*7);
    for(int k=1;k<=n;k++){ out+=to_string(R[k]%MOD); out+='\n'; }
    fputs(out.c_str(),stdout);
}
