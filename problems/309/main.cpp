#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,q; scanf("%d %d",&n,&q);
    vector<int> coin(n+1);
    for(int i=1;i<=n;i++) scanf("%d",&coin[i]);
    vector<vector<int>> g(n+1);
    for(int i=0;i<n-1;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);g[b].push_back(a);}
    const int INF=INT_MAX;
    vector<int> gd(n+1,INF);
    {queue<int> bq; for(int i=1;i<=n;i++) if(coin[i]){gd[i]=0;bq.push(i);}
     while(!bq.empty()){int u=bq.front();bq.pop();for(int v:g[u])if(gd[v]==INF){gd[v]=gd[u]+1;bq.push(v);}}}
    int LOG=1; while((1<<LOG)<max(2,n))LOG++;
    vector<vector<int>> up(LOG+1, vector<int>(n+1,0));
    vector<vector<int>> mn(LOG+1, vector<int>(n+1,INF));
    vector<int> depth(n+1,0);
    {vector<char> vis(n+1,0); vector<int> stk={1}; vis[1]=1; up[0][1]=1; mn[0][1]=gd[1];
     while(!stk.empty()){int u=stk.back();stk.pop_back();
        for(int v:g[u])if(!vis[v]){vis[v]=1;depth[v]=depth[u]+1;up[0][v]=u;mn[0][v]=gd[v];stk.push_back(v);}}}
    for(int k=1;k<=LOG;k++)for(int v=1;v<=n;v++){up[k][v]=up[k-1][up[k-1][v]];mn[k][v]=min(mn[k-1][v],mn[k-1][up[k-1][v]]);}
    auto LCA=[&](int u,int v){ if(depth[u]<depth[v])swap(u,v); int d=depth[u]-depth[v]; for(int k=0;k<=LOG;k++) if(d>>k&1)u=up[k][u]; if(u==v)return u; for(int k=LOG;k>=0;k--) if(up[k][u]!=up[k][v]){u=up[k][u];v=up[k][v];} return up[0][u]; };
    auto climb=[&](int u,int anc)->int{ int d=depth[u]-depth[anc]; int res=INF; for(int k=0;k<=LOG;k++) if(d>>k&1){res=min(res,mn[k][u]);u=up[k][u];} return res; };
    string out; out.reserve(q*4);
    while(q--){
        int a,b; scanf("%d %d",&a,&b);
        int l=LCA(a,b);
        int mg=min(min(climb(a,l),climb(b,l)),gd[l]);
        long long dist=(long long)depth[a]+depth[b]-2*depth[l];
        out += to_string(dist + 2LL*mg); out+='\n';
    }
    fputs(out.c_str(), stdout);
}
