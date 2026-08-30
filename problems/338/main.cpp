#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
long long pw(long long a,long long b){a%=MOD;long long r=1;while(b){if(b&1)r=r*a%MOD;a=a*a%MOD;b>>=1;}return r;}
int main(){
    int n; scanf("%d",&n);
    int maxE = n*(n-1)/2;
    vector<long long> pw2(maxE+1); pw2[0]=1; for(int i=1;i<=maxE;i++) pw2[i]=pw2[i-1]*2%MOD;
    vector<long long> fact(n+1), inv(n+1);
    fact[0]=1; for(int i=1;i<=n;i++) fact[i]=fact[i-1]*i%MOD;
    inv[n]=pw(fact[n],MOD-2); for(int i=n;i>0;i--) inv[i-1]=inv[i]*i%MOD;
    auto C=[&](int a,int b)->long long{ if(b<0||b>a)return 0; return fact[a]*inv[b]%MOD*inv[a-b]%MOD; };
    auto c2=[&](int m){ return (long long)m*(m-1)/2; };
    // s(m) = number of strongly connected tournaments on m nodes
    vector<long long> s(n+1,0);
    for(int m=1;m<=n;m++){
        long long v=pw2[c2(m)];
        for(int k=1;k<m;k++) v=(v - C(m,k)*s[k]%MOD*pw2[c2(m-k)])%MOD;
        v%=MOD; if(v<0)v+=MOD; s[m]=v;
    }
    // G[m]=s(m)/m!  (EGF); f(n,j)=n![x^n] g^j ; output f(n,1..n)
    vector<long long> G(n+1,0); for(int m=1;m<=n;m++) G[m]=s[m]*inv[m]%MOD;
    vector<long long> cur(n+1,0); for(int m=0;m<=n;m++) cur[m]=G[m]; // g^1
    vector<long long> ans(n+1,0);
    ans[1]=fact[n]*cur[n]%MOD;
    for(int j=2;j<=n;j++){
        vector<long long> nx(n+1,0);
        // convolution nx = cur * G, truncated to degree n ; G[0]=0
        for(int a=1;a<=n;a++){ if(!G[a])continue; for(int d=a; d<=n; d++){ if(cur[d-a]) nx[d]=(nx[d]+G[a]*cur[d-a])%MOD; } }
        cur.swap(nx);
        ans[j]=fact[n]*cur[n]%MOD;
    }
    string out; out.reserve(n*7);
    for(int j=1;j<=n;j++){ out+=to_string(ans[j]%MOD); out+='\n'; }
    fputs(out.c_str(),stdout);
}
