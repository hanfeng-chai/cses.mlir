#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<long long> cost(m);
    for(int i=0;i<m;i++) scanf("%lld",&cost[i]);
    int total=n+m;
    vector<vector<pair<int,long long>>> g(total+1);
    for(int j=0;j<m;j++){
        int k; scanf("%d",&k);
        int comp=n+1+j;
        for(int t=0;t<k;t++){int a;scanf("%d",&a); g[a].push_back({comp,0}); g[comp].push_back({a,cost[j]}); }
    }
    vector<long long> dist(total+1, LLONG_MAX);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    dist[1]=0; pq.push({0,1});
    while(!pq.empty()){auto [d,u]=pq.top();pq.pop(); if(d>dist[u])continue; for(auto&pr:g[u]){ int v=pr.first; long long w=pr.second; if(d+w<dist[v]){dist[v]=d+w;pq.push({dist[v],v});}}}
    for(int i=1;i<=n;i++) printf("%lld ", dist[i]);
    printf("\n");
}
