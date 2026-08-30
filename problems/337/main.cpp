#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
long long pw(long long a,long long b){a%=MOD;long long r=1;while(b){if(b&1)r=r*a%MOD;a=a*a%MOD;b>>=1;}return r;}
int main(){
    char buf[5005]; scanf("%s",buf);
    string s=buf; int n=s.size();
    int c[26]={0}; for(char ch:s) c[ch-'a']++;
    vector<long long> fact(n+1), inv(n+1);
    fact[0]=1; for(int i=1;i<=n;i++) fact[i]=fact[i-1]*i%MOD;
    inv[n]=pw(fact[n],MOD-2); for(int i=n;i>0;i--) inv[i-1]=inv[i]*i%MOD;
    auto Cc=[&](int a,int b)->long long{ if(b<0||b>a)return 0; return fact[a]*inv[b]%MOD*inv[a-b]%MOD; };
    // dp[T] = sum over processed letters of prod_i [ (-1)^{c_i-k_i} C(c_i-1,k_i-1)/k_i! ], total blocks T
    vector<long long> dp(n+1,0); dp[0]=1; int curMax=0;
    for(int L=0;L<26;L++){
        if(c[L]==0) continue;
        int ci=c[L];
        vector<long long> nd(curMax+ci+1,0);
        // g(k) = (-1)^{ci-k} C(ci-1,k-1) * inv[k]   (1/k!)
        for(int T=0;T<=curMax;T++) if(dp[T]){
            for(int kk=1;kk<=ci;kk++){
                long long g=Cc(ci-1,kk-1)*inv[kk]%MOD;
                if((ci-kk)&1) g=(MOD-g)%MOD;
                nd[T+kk]=(nd[T+kk]+dp[T]*g)%MOD;
            }
        }
        curMax+=ci; dp.swap(nd);
    }
    long long ans=0;
    for(int T=0;T<=curMax;T++) ans=(ans+dp[T]*fact[T])%MOD;
    printf("%lld\n", ans);
}
