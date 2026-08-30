#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    const int LOG = 18;
    vector<vector<int>> adj(n + 1), up(LOG, vector<int>(n + 1, 0));
    for (int i = 0; i < n - 1; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); adj[b].push_back(a); }
    vector<int> depth(n + 1, 0);
    {
        vector<char> vis(n + 1, 0);
        queue<int> qq; qq.push(1); vis[1] = 1; up[0][1] = 0;
        while (!qq.empty()) { int u = qq.front(); qq.pop(); for (int v : adj[u]) if (!vis[v]) { vis[v] = 1; up[0][v] = u; depth[v] = depth[u] + 1; qq.push(v); } }
    }
    for (int j = 1; j < LOG; j++)
        for (int i = 1; i <= n; i++) up[j][i] = up[j - 1][up[j - 1][i]];
    auto lca = [&](int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int d = depth[a] - depth[b];
        for (int j = 0; j < LOG; j++) if (d >> j & 1) a = up[j][a];
        if (a == b) return a;
        for (int j = LOG - 1; j >= 0; j--) if (up[j][a] != up[j][b]) { a = up[j][a]; b = up[j][b]; }
        return up[0][a];
    };
    while (q--) { int a, b; scanf("%d %d", &a, &b); int l = lca(a, b); printf("%d\n", depth[a] + depth[b] - 2 * depth[l]); }
}
