#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b); indeg[b]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++) if (indeg[i] == 0) q.push(i);
    vector<int> dp(n + 1, -1), par(n + 1, 0);
    dp[1] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dp[u] != -1 && dp[u] + 1 > dp[v]) { dp[v] = dp[u] + 1; par[v] = u; }
            if (--indeg[v] == 0) q.push(v);
        }
    }
    if (dp[n] == -1) { printf("IMPOSSIBLE\n"); return 0; }
    vector<int> path;
    for (int x = n; x; x = par[x]) path.push_back(x);
    reverse(path.begin(), path.end());
    printf("%d\n", (int)path.size());
    for (size_t i = 0; i < path.size(); i++) printf("%d%c", path[i], " \n"[i + 1 == path.size()]);
}
