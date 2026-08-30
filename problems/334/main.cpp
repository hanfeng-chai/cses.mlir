#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<pair<int,int>> trap(m);
    for(int i=0;i<m;i++){int y,x;scanf("%d %d",&y,&x);trap[i]={y,x};}
    int MX=2*n+5;
    vector<long long> fact(MX), inv(MX);
    fact[0]=1; for(int i=1;i<MX;i++) fact[i]=fact[i-1]*i%MOD;
    // inverse via fermat on last
    auto pw=[&](long long a,long long b){long long r=1;a%=MOD;while(b){if(b&1)r=r*a%MOD;a=a*a%MOD;b>>=1;}return r;};
    inv[MX-1]=pw(fact[MX-1],MOD-2); for(int i=MX-1;i>0;i--) inv[i-1]=inv[i]*i%MOD;
    auto C=[&](int a,int b)->long long{ if(b<0||b>a||a<0)return 0; return fact[a]*inv[b]%MOD*inv[a-b]%MOD; };
    // paths from (1,1) to (y,x) = C(y+x-2, y-1)
    auto paths=[&](int y1,int x1,int y2,int x2)->long long{ int dy=y2-y1, dx=x2-x1; if(dy<0||dx<0)return 0; return C(dy+dx, dy); };
    sort(trap.begin(),trap.end()); // by y then x
    vector<long long> f(m);
    for(int i=0;i<m;i++){
        f[i]=paths(1,1,trap[i].first,trap[i].second);
        for(int j=0;j<i;j++){
            if(trap[j].first<=trap[i].first && trap[j].second<=trap[i].second)
                f[i]=(f[i]-f[j]*paths(trap[j].first,trap[j].second,trap[i].first,trap[i].second))%MOD;
        }
        f[i]%=MOD; if(f[i]<0)f[i]+=MOD;
    }
    long long ans=paths(1,1,n,n);
    for(int i=0;i<m;i++) ans=(ans-f[i]*paths(trap[i].first,trap[i].second,n,n))%MOD;
    ans%=MOD; if(ans<0)ans+=MOD;
    printf("%lld\n", ans);
}
