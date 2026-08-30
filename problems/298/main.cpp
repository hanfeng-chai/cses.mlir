#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<vector<int>> radj(n+1);
    vector<int> indeg(n+1,0);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b); radj[b].push_back(a); indeg[a]++; }
    priority_queue<int> pq;
    for(int v=1;v<=n;v++) if(indeg[v]==0) pq.push(v);
    vector<int> order; order.reserve(n);
    while(!pq.empty()){
        int u=pq.top();pq.pop(); order.push_back(u);
        for(int w: radj[u]) if(--indeg[w]==0) pq.push(w);
    }
    reverse(order.begin(),order.end());
    for(int i=0;i<n;i++) printf("%d ", order[i]);
    printf("\n");
}
