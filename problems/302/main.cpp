#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<vector<int>> g(n+1);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);g[b].push_back(a);}
    const int INF=INT_MAX;
    int ans=INF;
    vector<int> dist(n+1), par(n+1);
    for(int s=1;s<=n;s++){
        fill(dist.begin(),dist.end(),-1);
        dist[s]=0; par[s]=-1;
        queue<int> q; q.push(s);
        while(!q.empty()){
            int u=q.front();q.pop();
            if(2*dist[u] >= ans) break;
            for(int v: g[u]){
                if(dist[v]==-1){ dist[v]=dist[u]+1; par[v]=u; q.push(v); }
                else if(v!=par[u]) ans=min(ans, dist[u]+dist[v]+1);
            }
        }
    }
    printf("%d\n", ans==INF? -1 : ans);
}
