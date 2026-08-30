#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<vector<pair<int,int>>> g(n+1);
    vector<int> ea(m), eb(m);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);ea[i]=a;eb[i]=b;g[a].push_back({b,i});g[b].push_back({a,i});}
    vector<int> disc(n+1,0), low(n+1,0); int timer=0;
    vector<char> treeEdge(m,0);
    vector<int> it_(n+1,0);
    bool bridge=false; int comps=0;
    for(int s=1;s<=n;s++){
        if(disc[s]) continue;
        comps++;
        vector<pair<int,int>> stk; stk.push_back({s,-1}); disc[s]=low[s]=++timer;
        while(!stk.empty()){
            int u=stk.back().first, pe=stk.back().second;
            if(it_[u] < (int)g[u].size()){
                auto pr=g[u][it_[u]++]; int v=pr.first, id=pr.second;
                if(id==pe) continue;
                if(!disc[v]){ treeEdge[id]=1; disc[v]=low[v]=++timer; stk.push_back({v,id}); }
                else low[u]=min(low[u],disc[v]);
            } else {
                stk.pop_back();
                if(!stk.empty()){ int par=stk.back().first; low[par]=min(low[par],low[u]); if(low[u]>disc[par]) bridge=true; }
            }
        }
    }
    bool connected=(comps==1);
    if(bridge||!connected){ printf("IMPOSSIBLE\n"); return 0; }
    string out; out.reserve((size_t)m*8);
    for(int i=0;i<m;i++){ int a=ea[i],b=eb[i],from,to;
        if(treeEdge[i]){ if(disc[a]<disc[b]){from=a;to=b;}else{from=b;to=a;} }
        else { if(disc[a]>disc[b]){from=a;to=b;}else{from=b;to=a;} }
        out+=to_string(from);out+=' ';out+=to_string(to);out+='\n'; }
    fputs(out.c_str(),stdout);
}
