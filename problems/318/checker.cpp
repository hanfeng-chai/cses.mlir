#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int N;
vector<vector<int>> g;
vector<int> matchL, matchR, dist;
bool bfs(){
    queue<int> q;
    for(int u=1;u<=N;u++){ if(matchL[u]==0){dist[u]=0;q.push(u);} else dist[u]=INT_MAX; }
    bool found=false;
    while(!q.empty()){int u=q.front();q.pop(); for(int v:g[u]){ int w=matchR[v]; if(w==0) found=true; else if(dist[w]==INT_MAX){dist[w]=dist[u]+1;q.push(w);} } }
    return found;
}
bool dfs(int u){
    for(int v:g[u]){ int w=matchR[v]; if(w==0 || (dist[w]==dist[u]+1 && dfs(w))){ matchL[u]=v; matchR[v]=u; return true; } }
    dist[u]=INT_MAX; return false;
}
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    int n=inf.readInt(), m=inf.readInt(); N=n;
    g.assign(n+1,{});
    set<pair<int,int>> es;
    for(int i=0;i<m;i++){int a=inf.readInt(),b=inf.readInt(); g[a].push_back(b); es.insert({a,b});}
    matchL.assign(n+1,0); matchR.assign(n+1,0); dist.assign(n+1,0);
    int matching=0; while(bfs()){ for(int u=1;u<=n;u++) if(matchL[u]==0 && dfs(u)) matching++; }
    int cover=n-matching;
    string first=ouf.readToken();
    if(first=="NO"){ if(cover<=2) quitf(_wa,"said NO but two paths exist (min path cover=%d)",cover); quitf(_ok,"correctly NO"); }
    if(first!="YES") quitf(_wa,"expected YES or NO, got %s",first.c_str());
    if(cover>2) quitf(_wa,"said YES but min path cover is %d > 2",cover);
    vector<char> used(n+1,0); int totalNodes=0;
    for(int p=0;p<2;p++){
        int c=ouf.readInt(0,n);
        totalNodes+=c;
        int prev=-1;
        for(int i=0;i<c;i++){ int x=ouf.readInt(1,n); if(used[x]) quitf(_wa,"node %d appears in more than one place",x); used[x]=1; if(prev!=-1 && !es.count({prev,x})) quitf(_wa,"no edge %d->%d in graph",prev,x); prev=x; }
    }
    if(totalNodes!=n) quitf(_wa,"paths cover %d nodes, expected %d",totalNodes,n);
    quitf(_ok,"valid two-path cover");
}
