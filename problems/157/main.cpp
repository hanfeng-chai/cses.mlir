#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); adj[b].push_back(a); }
    vector<int> par(n + 1, 0), order; order.reserve(n);
    {
        vector<char> vis(n + 1, 0); vis[1] = 1;
        vector<int> st = {1};
        while (!st.empty()) { int u = st.back(); st.pop_back(); order.push_back(u); for (int v : adj[u]) if (!vis[v]) { vis[v] = 1; par[v] = u; st.push_back(v); } }
    }
    vector<int> sz(n + 1, 1);
    for (int i = (int)order.size() - 1; i >= 0; i--) { int u = order[i]; if (par[u]) sz[par[u]] += sz[u]; }
    vector<int> maxsub(n + 1, 0);
    for (int u = 1; u <= n; u++) if (par[u]) maxsub[par[u]] = max(maxsub[par[u]], sz[u]);
    int cent = 1;
    for (int u = 1; u <= n; u++) {
        int part = max(n - sz[u], maxsub[u]);  // heaviest component when rooted at u
        if (part <= n / 2) { cent = u; break; }
    }
    printf("%d\n", cent);
}
