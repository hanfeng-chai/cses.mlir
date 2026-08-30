#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); adj[b].push_back(a); }
    vector<int> par(n + 1, 0), order; order.reserve(n);
    vector<char> vis(n + 1, 0);
    vector<int> st = {1}; vis[1] = 1;
    while (!st.empty()) { int u = st.back(); st.pop_back(); order.push_back(u); for (int v : adj[u]) if (!vis[v]) { vis[v] = 1; par[v] = u; st.push_back(v); } }
    vector<long long> sz(n + 1, 1), down(n + 1, 0);
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        for (int v : adj[u]) if (v != par[u]) { sz[u] += sz[v]; down[u] += down[v] + sz[v]; }
    }
    vector<long long> ans(n + 1, 0);
    ans[1] = down[1];
    for (int u : order)  // pre-order: parent before child
        for (int v : adj[u]) if (v != par[u]) ans[v] = ans[u] - sz[v] + (n - sz[v]);
    for (int i = 1; i <= n; i++) printf("%lld%c", ans[i], " \n"[i == n]);
}
