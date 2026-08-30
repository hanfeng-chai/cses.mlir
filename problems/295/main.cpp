#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    vector<int> shop(k);
    for(auto&x:shop) scanf("%d",&x);
    vector<vector<int>> g(n+1);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);g[a].push_back(b);g[b].push_back(a);}
    const int INF=INT_MAX;
    vector<int> d0(n+1,INF), r0(n+1,0), d1(n+1,INF), r1(n+1,0);
    queue<array<int,3>> q;
    for(int s: shop) q.push({0,s,s});
    while(!q.empty()){
        auto e=q.front();q.pop();
        int dist=e[0],u=e[1],root=e[2];
        int cntLabel = (d0[u]!=INF) + (d1[u]!=INF);
        if(cntLabel==2) continue;
        if(cntLabel==1 && r0[u]==root) continue;
        if(cntLabel==0){ d0[u]=dist; r0[u]=root; }
        else { d1[u]=dist; r1[u]=root; }
        for(int v: g[u]) if(d1[v]==INF) q.push({dist+1,v,root});
    }
    for(int v=1;v<=n;v++){
        int ans;
        if(d0[v]==0) ans = (d1[v]==INF)? -1 : d1[v]; // v is a shop -> nearest OTHER shop
        else ans = (d0[v]==INF)? -1 : d0[v];
        printf("%d ", ans);
    }
    printf("\n");
}
