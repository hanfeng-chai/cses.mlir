#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m,q; scanf("%d %d %d",&n,&m,&q);
    vector<vector<int>> g(n+1);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);g[b].push_back(a);}
    const unsigned short INF=0xFFFF;
    // de[s][t], do_[s][t] : shortest even/odd length walk; flat arrays
    vector<unsigned short> de((size_t)n*n, INF), od((size_t)n*n, INF);
    vector<array<unsigned short,2>> dist(n+1);
    for(int s=1;s<=n;s++){
        for(int v=1;v<=n;v++){ dist[v][0]=INF; dist[v][1]=INF; }
        dist[s][0]=0;
        // BFS on (node,parity)
        deque<pair<int,int>> bq; bq.push_back({s,0});
        while(!bq.empty()){
            auto [u,p]=bq.front(); bq.pop_front();
            int nd=dist[u][p]+1; int np=p^1;
            for(int v: g[u]) if(dist[v][np]==INF){ dist[v][np]=(unsigned short)nd; bq.push_back({v,np}); }
        }
        size_t base=(size_t)(s-1)*n;
        for(int t=1;t<=n;t++){ de[base+t-1]=dist[t][0]; od[base+t-1]=dist[t][1]; }
    }
    string out; out.reserve(q*4);
    while(q--){
        int a,b; long long x; scanf("%d %d %lld",&a,&b,&x);
        size_t idx=(size_t)(a-1)*n+(b-1);
        bool ok;
        if(x%2==0) ok = (de[idx]!=INF && de[idx]<=x);
        else ok = (od[idx]!=INF && od[idx]<=x);
        out += ok? "YES\n" : "NO\n";
    }
    fputs(out.c_str(), stdout);
}
