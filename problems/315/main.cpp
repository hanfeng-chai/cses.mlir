#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<vector<pair<int,int>>> g(n+1), rgr(n+1);
    vector<array<int,3>> edges(m);
    for(int i=0;i<m;i++){int a,b,c;scanf("%d %d %d",&a,&b,&c);edges[i]={a,b,c};g[a].push_back({b,c});rgr[b].push_back({a,c});}
    const ll INF=1e18;
    auto dijkstra=[&](int src, vector<vector<pair<int,int>>>&adj){
        vector<ll> dist(n+1,INF); dist[src]=0;
        priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq; pq.push({0,src});
        while(!pq.empty()){auto [dd,u]=pq.top();pq.pop(); if(dd>dist[u])continue; for(auto [v,w]:adj[u]) if(dd+w<dist[v]){dist[v]=dd+w;pq.push({dist[v],v});}}
        return dist;
    };
    auto d1=dijkstra(1,g);
    auto d2=dijkstra(n,rgr);
    ll D=d1[n];
    vector<vector<int>> pred(n+1);
    for(int i=0;i<m;i++){int a=edges[i][0],b=edges[i][1],c=edges[i][2]; if(d1[a]<INF && d2[b]<INF && d1[a]+(ll)c+d2[b]==D) pred[b].push_back(a);}
    vector<int> nodes;
    for(int v=1;v<=n;v++) if(d1[v]<INF && d2[v]<INF && d1[v]+d2[v]==D) nodes.push_back(v);
    sort(nodes.begin(),nodes.end(),[&](int a,int b){return d1[a]<d1[b];});
    int LOG=1; while((1<<LOG)<max(2,n)) LOG++;
    vector<int> idom(n+1,-1), domDepth(n+1,0);
    vector<vector<int>> upd(LOG+1, vector<int>(n+1,0));
    auto lcaDom=[&](int a,int b){ if(domDepth[a]<domDepth[b])swap(a,b); int dd=domDepth[a]-domDepth[b]; for(int k=0;k<=LOG;k++) if(dd>>k&1)a=upd[k][a]; if(a==b)return a; for(int k=LOG;k>=0;k--) if(upd[k][a]!=upd[k][b]){a=upd[k][a];b=upd[k][b];} return upd[0][a]; };
    idom[1]=1; domDepth[1]=0; for(int k=0;k<=LOG;k++) upd[k][1]=1;
    for(int v: nodes){ if(v==1) continue;
        int ni=-1; for(int p: pred[v]){ if(idom[p]==-1) continue; ni = (ni==-1)? p : lcaDom(ni,p); }
        if(ni==-1) continue;
        idom[v]=ni; domDepth[v]=domDepth[ni]+1; upd[0][v]=ni;
        for(int k=1;k<=LOG;k++) upd[k][v]=upd[k-1][upd[k-1][v]];
    }
    vector<int> crit; int x=n;
    while(true){ crit.push_back(x); if(x==1)break; x=idom[x]; }
    sort(crit.begin(),crit.end());
    printf("%d\n",(int)crit.size());
    string out; for(int c:crit){ out+=to_string(c); out+=' '; } out+='\n';
    fputs(out.c_str(),stdout);
}
