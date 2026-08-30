#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,m; scanf("%d %d",&n,&m);
    vector<vector<pair<int,long long>>> adj(n+1); // node -> (neighbor, P[neighbor]-P[node])
    for(int i=0;i<m;i++){
        int l,r; long long s; scanf("%d %d %lld",&l,&r,&s);
        int u=l-1, v=r; // P[v]-P[u]=s
        adj[u].push_back({v, s});
        adj[v].push_back({u, -s});
    }

    vector<char> visited(n+1,0);
    vector<long long> P(n+1,0);
    bool ok=true;

    for(int start=0; start<=n && ok; start++){
        if(visited[start]) continue;
        visited[start]=1;
        P[start]=0; // arbitrary root value (node 0's root MUST be 0, others can be anything)
        queue<int> q; q.push(start);
        while(!q.empty() && ok){
            int u=q.front(); q.pop();
            for(auto&e: adj[u]){
                int v=e.first; long long delta=e.second;
                long long want = P[u]+delta;
                if(!visited[v]){
                    visited[v]=1; P[v]=want; q.push(v);
                } else if(P[v]!=want){
                    ok=false; break;
                }
            }
        }
    }

    if(!ok){ printf("NO\n"); return 0; }

    printf("YES\n");
    string out; out.reserve(n*8);
    for(int i=1;i<=n;i++){
        out += to_string(P[i]-P[i-1]);
        out += (i==n) ? '\n' : ' ';
    }
    fputs(out.c_str(), stdout);
}
