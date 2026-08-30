#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b); adj[b].push_back(a);
    }
    vector<int> dist(n + 1, -1), par(n + 1, 0);
    queue<int> q;
    q.push(1); dist[1] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u])
            if (dist[v] == -1) { dist[v] = dist[u] + 1; par[v] = u; q.push(v); }
    }
    if (dist[n] == -1) { printf("IMPOSSIBLE\n"); return 0; }
    vector<int> path;
    for (int x = n; x; x = par[x]) path.push_back(x);
    reverse(path.begin(), path.end());
    printf("%d\n", (int)path.size());
    for (size_t i = 0; i < path.size(); i++) printf("%d%c", path[i], " \n"[i + 1 == path.size()]);
}
