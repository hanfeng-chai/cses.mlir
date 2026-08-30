#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m,q; scanf("%d %d %d",&n,&m,&q);
    vector<vector<pair<int,int>>> g(n+1);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b); if(a==b) continue; g[a].push_back({b,i}); g[b].push_back({a,i});}
    vector<int> disc(n+1,0), low(n+1,0); int timer=0;
    vector<char> art(n+1,0);
    vector<int> it_(n+1,0), parentEdge(n+1,-1);
    vector<pair<int,int>> estk;
    vector<vector<int>> bccs;
    for(int s=1;s<=n;s++){
        if(disc[s]) continue;
        vector<int> stk; stk.push_back(s); disc[s]=low[s]=++timer; parentEdge[s]=-1;
        int rootChildren=0;
        while(!stk.empty()){
            int u=stk.back();
            if(it_[u] < (int)g[u].size()){
                auto pr=g[u][it_[u]++]; int v=pr.first, id=pr.second;
                if(id==parentEdge[u]) continue;
                if(!disc[v]){
                    estk.push_back({u,v});
                    parentEdge[v]=id;
                    disc[v]=low[v]=++timer;
                    if(u==s) rootChildren++;
                    stk.push_back(v);
                } else if(disc[v]<disc[u]){
                    estk.push_back({u,v});
                    low[u]=min(low[u],disc[v]);
                }
            } else {
                stk.pop_back();
                if(!stk.empty()){
                    int p=stk.back();
                    low[p]=min(low[p],low[u]);
                    if(low[u]>=disc[p]){
                        if(p!=s) art[p]=1;
                        vector<int> vs;
                        while(!estk.empty()){
                            auto e=estk.back(); estk.pop_back();
                            vs.push_back(e.first); vs.push_back(e.second);
                            if(e.first==p && e.second==u) break;
                        }
                        sort(vs.begin(),vs.end()); vs.erase(unique(vs.begin(),vs.end()),vs.end());
                        bccs.push_back(move(vs));
                    }
                }
            }
        }
        if(rootChildren>=2) art[s]=1;
    }
    int totalNodes = n + (int)bccs.size();
    vector<vector<int>> tadj(totalNodes+1);
    vector<int> rep(n+1,0);
    for(int v=1;v<=n;v++) if(art[v]) rep[v]=v;
    for(int i=0;i<(int)bccs.size();i++){
        int bnode = n + 1 + i;
        for(int x: bccs[i]){
            if(art[x]){ tadj[bnode].push_back(x); tadj[x].push_back(bnode); }
            else rep[x]=bnode;
        }
    }
    for(int v=1;v<=n;v++) if(rep[v]==0) rep[v]=v;
    int LOG=1; while((1<<LOG)<max(2,totalNodes)) LOG++;
    vector<vector<int>> up(LOG+1, vector<int>(totalNodes+1,0));
    vector<int> depth(totalNodes+1,0);
    vector<char> vis(totalNodes+1,0);
    for(int s=1;s<=totalNodes;s++) if(!vis[s]){
        vis[s]=1; up[0][s]=s;
        queue<int> bq; bq.push(s);
        while(!bq.empty()){int u=bq.front();bq.pop(); for(int v:tadj[u]) if(!vis[v]){vis[v]=1;depth[v]=depth[u]+1;up[0][v]=u;bq.push(v);}}
    }
    for(int k=1;k<=LOG;k++) for(int v=1;v<=totalNodes;v++) up[k][v]=up[k-1][up[k-1][v]];
    auto LCA=[&](int u,int v){ if(depth[u]<depth[v])swap(u,v); int dd=depth[u]-depth[v]; for(int k=0;k<=LOG;k++) if(dd>>k&1)u=up[k][u]; if(u==v)return u; for(int k=LOG;k>=0;k--) if(up[k][u]!=up[k][v]){u=up[k][u];v=up[k][v];} return up[0][u]; };
    auto isAnc=[&](int x,int u){ if(depth[x]>depth[u]) return false; int dd=depth[u]-depth[x],uu=u; for(int k=0;k<=LOG;k++) if(dd>>k&1)uu=up[k][uu]; return uu==x; };
    string out; out.reserve(q*4);
    while(q--){
        int a,b,c; scanf("%d %d %d",&a,&b,&c);
        bool yes;
        if(a==c||b==c) yes=false;
        else if(!art[c]) yes=true;
        else {
            int u=rep[a], v=rep[b], x=c;
            int l=LCA(u,v);
            bool onPath = (depth[x]>=depth[l]) && (isAnc(x,u)||isAnc(x,v));
            yes = !onPath;
        }
        out += yes? "YES\n":"NO\n";
    }
    fputs(out.c_str(),stdout);
}
