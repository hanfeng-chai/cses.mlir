#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
const int MAXV=5001;

int main(){
    int n; scanf("%d",&n);
    vector<int> x(n);
    for(auto&v:x) scanf("%d",&v);

    vector<int> spf(MAXV,0);
    for(int i=2;i<MAXV;i++)
        if(spf[i]==0)
            for(int j=i;j<MAXV;j+=i)
                if(spf[j]==0) spf[j]=i;

    vector<int> primeIndex(MAXV,-1);
    int dim=0;
    for(int i=2;i<MAXV;i++) if(spf[i]==i) primeIndex[i]=dim++;

    vector<bitset<700>> basis(dim);
    vector<char> hasBasis(dim,0);
    int rank=0;

    for(int i=0;i<n;i++){
        int v=x[i];
        bitset<700> vec;
        while(v>1){
            int p=spf[v]; int e=0;
            while(v%p==0){ v/=p; e++; }
            if(e&1) vec[primeIndex[p]]=1;
        }
        for(int b=dim-1;b>=0;b--){
            if(!vec[b]) continue;
            if(hasBasis[b]) vec ^= basis[b];
            else { basis[b]=vec; hasBasis[b]=1; rank++; break; }
        }
    }

    long long ans=1;
    for(int i=0;i<n-rank;i++) ans=ans*2%MOD;
    printf("%lld\n", ans);
}
