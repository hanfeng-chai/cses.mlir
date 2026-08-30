#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,q; scanf("%d %d",&n,&q);
    vector<int> coin(n+1); int root=1;
    for(int i=1;i<=n;i++){scanf("%d",&coin[i]); if(coin[i])root=i;}
    vector<vector<int>> g(n+1);
    for(int i=0;i<n-1;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);g[b].push_back(a);}
    int LOG=1; while((1<<LOG)<max(2,n))LOG++;
    vector<vector<int>> up(LOG+1, vector<int>(n+1,0));
    vector<int> depth(n+1,0), par(n+1,0), order; order.reserve(n);
    {vector<char> vis(n+1,0); vector<int> stk={root}; vis[root]=1; up[0][root]=root;
     while(!stk.empty()){int u=stk.back();stk.pop_back();order.push_back(u);for(int v:g[u])if(!vis[v]){vis[v]=1;depth[v]=depth[u]+1;up[0][v]=u;par[v]=u;stk.push_back(v);}}}
    for(int k=1;k<=LOG;k++)for(int v=1;v<=n;v++)up[k][v]=up[k-1][up[k-1][v]];
    vector<int> cnt(n+1,0);
    for(int i=(int)order.size()-1;i>=0;i--){int u=order[i]; cnt[u]+=coin[u]; if(par[u]) cnt[par[u]]+=cnt[u];}
    vector<char> inK(n+1,0); int Ksize=0;
    for(int v=1;v<=n;v++){ inK[v]= cnt[v]>0; if(inK[v])Ksize++; }
    long long Ck=Ksize-1;
    vector<int> entry(n+1,0);
    for(int u: order){ entry[u]= inK[u]? u : entry[par[u]]; }
    vector<int> dK(n+1,0);
    for(int v=1;v<=n;v++) dK[v]=depth[v]-depth[entry[v]];
    auto LCA=[&](int u,int v){ if(depth[u]<depth[v])swap(u,v); int d=depth[u]-depth[v]; for(int k=0;k<=LOG;k++)if(d>>k&1)u=up[k][u]; if(u==v)return u; for(int k=LOG;k>=0;k--)if(up[k][u]!=up[k][v]){u=up[k][u];v=up[k][v];} return up[0][u]; };
    string out; out.reserve(q*4);
    while(q--){
        int a,b; scanf("%d %d",&a,&b);
        int l=LCA(a,b);
        long long dist=(long long)depth[a]+depth[b]-2*depth[l];
        long long E=Ck+dK[a]+dK[b];
        if(entry[a]==entry[b]) E -= (dK[a]+dK[b]-dist)/2;
        out += to_string(2*E - dist); out+='\n';
    }
    fputs(out.c_str(), stdout);
}
