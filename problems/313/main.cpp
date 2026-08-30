#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int par_[100005];
int findp(int x){while(par_[x]!=x)x=par_[x]=par_[par_[x]];return x;}
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<vector<int>> g(n+1);
    vector<pair<int,int>> reqs(m);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);reqs[i]={a,b};}
    // iterative Tarjan SCC
    vector<int> comp(n+1,-1), low(n+1,0), disc(n+1,0); int timer=0, sccCnt=0;
    vector<int> stk; vector<char> onstk(n+1,0);
    vector<int> it_(n+1,0);
    for(int s=1;s<=n;s++){
        if(disc[s]) continue;
        vector<int> dfs; dfs.push_back(s);
        while(!dfs.empty()){
            int u=dfs.back();
            if(!disc[u]){ disc[u]=low[u]=++timer; stk.push_back(u); onstk[u]=1; }
            bool pushed=false;
            while(it_[u]<(int)g[u].size()){
                int w=g[u][it_[u]++];
                if(!disc[w]){ dfs.push_back(w); pushed=true; break; }
                else if(onstk[w]) low[u]=min(low[u],disc[w]);
            }
            if(pushed) continue;
            if(low[u]==disc[u]){
                while(true){ int x=stk.back();stk.pop_back();onstk[x]=0;comp[x]=sccCnt; if(x==u)break; }
                sccCnt++;
            }
            dfs.pop_back();
            if(!dfs.empty()){ int p=dfs.back(); low[p]=min(low[p],low[u]); }
        }
    }
    vector<int> sccSize(sccCnt,0);
    for(int v=1;v<=n;v++) sccSize[comp[v]]++;
    // Weakly-connected components of the request graph over all n nodes.
    // Per component of N nodes: a topological chain needs N-1 arcs and realizes all requests;
    // if the component contains a cyclic (non-trivial SCC) requirement it needs one cycle, so N arcs
    // (a single big cycle through all N nodes covers every internal mutual-reachability + the rest).
    for(int v=1;v<=n;v++) par_[v]=v;
    for(auto&pr:reqs){ int ra=findp(pr.first), rb=findp(pr.second); if(ra!=rb) par_[ra]=rb; }
    int C=0; for(int v=1;v<=n;v++) if(findp(v)==v) C++;
    vector<char> hasCycle(n+1,0);
    for(int v=1;v<=n;v++) if(sccSize[comp[v]]>=2) hasCycle[findp(v)]=1;
    int C_nt=0; for(int v=1;v<=n;v++) if(findp(v)==v && hasCycle[v]) C_nt++;
    printf("%lld\n", (ll)n - C + C_nt);
}
