#include <bits/stdc++.h>
using namespace std;
int par[200005]; long long sz[200005];
int find(int x){while(par[x]!=x)x=par[x]=par[par[x]];return x;}
int main(){
    int n; scanf("%d",&n);
    vector<array<int,3>> e;
    for(int i=0;i<n-1;i++){int a,b,w;scanf("%d %d %d",&a,&b,&w);e.push_back({w,a,b});}
    sort(e.begin(),e.end(),[](const array<int,3>&A,const array<int,3>&B){return A[0]>B[0];});
    for(int i=1;i<=n;i++){par[i]=i;sz[i]=1;}
    long long ans=0;
    for(auto&ed:e){int w=ed[0],a=ed[1],b=ed[2];int ra=find(a),rb=find(b);
        ans += sz[ra]*sz[rb]*(long long)w; par[ra]=rb; sz[rb]+=sz[ra];
    }
    printf("%lld\n", ans);
}
