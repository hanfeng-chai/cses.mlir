#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
long long pw(long long a,long long b){a%=MOD; long long r=1; while(b>0){ if(b&1) r=r*a%MOD; a=a*a%MOD; b>>=1;} return r;}

int main(){
    int n; scanf("%d",&n);
    vector<string> g(n);
    for(auto&r:g){ char buf[505]; scanf("%s",buf); r=buf; }

    vector<int> posA(n,-1), posB(n,-1);
    vector<char> colHasA(n,0), colHasB(n,0);
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){
        if(g[i][j]=='A'){ posA[i]=j; colHasA[j]=1; }
        else if(g[i][j]=='B'){ posB[i]=j; colHasB[j]=1; }
    }

    int nA=0,nB=0,nN=0;
    vector<int> Bonly_col, Aonly_col;
    for(int i=0;i<n;i++){
        bool a=posA[i]>=0, b=posB[i]>=0;
        if(a&&b) continue;
        else if(a){ nA++; Aonly_col.push_back(posA[i]); }
        else if(b){ nB++; Bonly_col.push_back(posB[i]); }
        else nN++;
    }

    int up=nB+nN, uq=nA+nN;
    int jp=0; for(int col: Bonly_col) if(!colHasA[col]) jp++;
    int jq=0; for(int col: Aonly_col) if(!colHasB[col]) jq++;
    int c=0; for(int col=0;col<n;col++) if(!colHasA[col] && !colHasB[col]) c++;

    vector<long long> fact(n+1), inv(n+1);
    fact[0]=1; for(int i=1;i<=n;i++) fact[i]=fact[i-1]*i%MOD;
    inv[n]=pw(fact[n],MOD-2); for(int i=n;i>0;i--) inv[i-1]=inv[i]*i%MOD;
    auto C=[&](int a,int b)->long long{ if(b<0||b>a||a<0) return 0; return fact[a]*inv[b]%MOD*inv[a-b]%MOD; };

    // R(pool,j,s) = # ways to complete a permutation on (pool-s) remaining slots
    // avoiding j forbidden (row,col) positions, via inclusion-exclusion
    auto R=[&](int pool,int j,int s)->long long{
        long long v=0;
        for(int t=0;t<=j;t++){
            long long term = C(j,t)*fact[pool-s-t]%MOD;
            if(t&1) v=(v-term+MOD)%MOD; else v=(v+term)%MOD;
        }
        return v;
    };

    long long ans=0;
    int smax=min(nN,c);
    long long falling=1;
    for(int s=0;s<=smax;s++){
        if(s>0) falling = falling*(c-s+1)%MOD;
        long long term = C(nN,s)*falling%MOD*R(up,jp,s)%MOD*R(uq,jq,s)%MOD;
        if(s&1) ans=(ans-term+MOD)%MOD; else ans=(ans+term)%MOD;
    }
    printf("%lld\n", ans);
}
