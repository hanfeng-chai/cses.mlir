#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<int>> adj(n + 1), radj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b); radj[b].push_back(a);
    }
    auto bfs = [&](vector<vector<int>> &g, int s) {
        vector<char> vis(n + 1, 0);
        queue<int> q; q.push(s); vis[s] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) if (!vis[v]) { vis[v] = 1; q.push(v); }
        }
        return vis;
    };
    auto f = bfs(adj, 1), r = bfs(radj, 1);
    for (int i = 1; i <= n; i++) if (!f[i]) { printf("NO\n1 %d\n", i); return 0; }
    for (int i = 1; i <= n; i++) if (!r[i]) { printf("NO\n%d 1\n", i); return 0; }
    printf("YES\n");
}
