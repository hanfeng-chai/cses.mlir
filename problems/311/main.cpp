#include <bits/stdc++.h>
using namespace std;
int n;
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
        map<vector<int>,int> canon;
        int c1=canonId(g1,1,canon), c2=canonId(g2,1,canon);
        puts(c1==c2?"YES":"NO");
    }
}
