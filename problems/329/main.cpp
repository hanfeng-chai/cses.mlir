#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
long long pw(long long a,long long b){a%=MOD; if(a<0)a+=MOD; long long r=1; while(b>0){ if(b&1) r=r*a%MOD; a=a*a%MOD; b>>=1;} return r;}

int main(){
    int t; scanf("%d",&t);
    vector<int> Nq(t), Aq(t), Bq(t);
    int N=1;
    for(int i=0;i<t;i++){ scanf("%d %d %d",&Nq[i],&Aq[i],&Bq[i]); N=max(N,Nq[i]); }

    vector<long long> fact(N+1), inv(N+1);
    fact[0]=1; for(int i=1;i<=N;i++) fact[i]=fact[i-1]*i%MOD;
    inv[N]=pw(fact[N],MOD-2); for(int i=N;i>0;i--) inv[i-1]=inv[i]*i%MOD;
    auto C=[&](int a,int b)->long long{ if(b<0||b>a||a<0) return 0; return fact[a]*inv[b]%MOD*inv[a-b]%MOD; };

    // Eulerian numbers Eu[m][d] = permutations of size m with exactly d excedances, d=0..m-1
    vector<vector<int>> Eu(N+1);
    Eu[1]={1};
    for(int m=2;m<=N;m++){
        Eu[m].assign(m,0);
        for(int d=0;d<m;d++){
            long long v=0;
            if(d<=m-2) v += (long long)(d+1)*Eu[m-1][d];
            if(d>=1 && d-1<=m-2) v += (long long)(m-d)*Eu[m-1][d-1];
            Eu[m][d]=(int)(v%MOD);
        }
    }
    auto Eget=[&](int mm,int jj)->long long{
        if(mm==0) return jj==0?1:0;
        if(jj<0 || jj>=mm) return 0;
        return Eu[mm][jj];
    };
    // Dexc(m,j) = # fixed-point-free permutations of size m with exactly j excedances
    auto Dexc=[&](int m,int j)->long long{
        long long s=0;
        for(int f=0;f<=m;f++){
            long long term = C(m,f) * Eget(m-f, j) % MOD;
            if(f&1) s=(s-term+MOD)%MOD; else s=(s+term)%MOD;
        }
        return s;
    };

    string out; out.reserve(t*8);
    for(int i=0;i<t;i++){
        int n=Nq[i], a=Aq[i], b=Bq[i];
        int m=a+b;
        long long ans=0;
        if(m<=n) ans = fact[n]*C(n,m)%MOD*Dexc(m,b)%MOD;
        out += to_string(ans); out += '\n';
    }
    fputs(out.c_str(), stdout);
}
