#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> findCenters(vector<vector<int>>& g){
    if(n<=2){ vector<int> r; for(int v=1;v<=n;v++) r.push_back(v); return r; }
    vector<int> deg(n+1); vector<char> rem(n+1,0);
    vector<int> layer;
    for(int v=1;v<=n;v++){deg[v]=g[v].size(); if(deg[v]==1) layer.push_back(v);}
    int remaining=n;
    while(remaining>2){
        for(int u:layer) rem[u]=1;
        remaining-=layer.size();
        vector<int> nxt;
        for(int u:layer) for(int v:g[u]) if(!rem[v]){ if(--deg[v]==1) nxt.push_back(v); }
        layer=nxt;
    }
    vector<int> res; for(int v=1;v<=n;v++) if(!rem[v]) res.push_back(v); return res;
}
int canonId(vector<vector<int>>&g,int root,map<vector<int>,int>&canon){
    vector<int> par(n+1,0), order; order.reserve(n); vector<char> vis(n+1,0);
    vector<int> stk={root}; vis[root]=1;
    while(!stk.empty()){int u=stk.back();stk.pop_back();order.push_back(u);for(int v:g[u])if(!vis[v]){vis[v]=1;par[v]=u;stk.push_back(v);}}
    vector<vector<int>> ch(n+1); vector<int> id(n+1,0);
    for(int i=(int)order.size()-1;i>=0;i--){int u=order[i]; sort(ch[u].begin(),ch[u].end());
        auto it=canon.find(ch[u]); int cid; if(it==canon.end()){cid=canon.size();canon[ch[u]]=cid;}else cid=it->second;
        id[u]=cid; if(par[u]) ch[par[u]].push_back(cid);}
    return id[root];
}
int main(){
    int t; scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        auto readTree=[&](){ vector<vector<int>> g(n+1); for(int i=0;i<n-1;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);g[b].push_back(a);} return g; };
        auto g1=readTree(); auto g2=readTree();
        auto c1=findCenters(g1); auto c2=findCenters(g2);
        map<vector<int>,int> canon;
        set<int> s1,s2;
        for(int r:c1) s1.insert(canonId(g1,r,canon));
        for(int r:c2) s2.insert(canonId(g2,r,canon));
        bool iso=false;
        for(int x:s1) if(s2.count(x)) iso=true;
        puts(iso?"YES":"NO");
    }
}
