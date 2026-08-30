#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
long long pw(long long a,long long b){a%=MOD;long long r=1;while(b){if(b&1)r=r*a%MOD;a=a*a%MOD;b>>=1;}return r;}
int main(){
    int n,k; scanf("%d %d",&n,&k);
    // surjections: sum_{i=0}^{k} (-1)^i C(k,i) (k-i)^n
    vector<long long> fact(k+1), inv(k+1);
    fact[0]=1; for(int i=1;i<=k;i++) fact[i]=fact[i-1]*i%MOD;
    inv[k]=pw(fact[k],MOD-2); for(int i=k;i>0;i--) inv[i-1]=inv[i]*i%MOD;
    auto C=[&](int a,int b){ if(b<0||b>a)return 0LL; return fact[a]*inv[b]%MOD*inv[a-b]%MOD; };
    long long ans=0;
    for(int i=0;i<=k;i++){
        long long term=C(k,i)*pw(k-i,n)%MOD;
        if(i&1) ans=(ans-term+MOD)%MOD; else ans=(ans+term)%MOD;
    }
    printf("%lld\n", ans);
}
