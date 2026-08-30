#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<pair<int, int>>> adj(n + 1);  // (to, edge id)
    vector<int> deg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back({b, i}); adj[b].push_back({a, i});
        deg[a]++; deg[b]++;
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] & 1) { printf("IMPOSSIBLE\n"); return 0; }  // odd degree -> no Euler circuit
    vector<char> used(m, 0);
    vector<int> ptr(n + 1, 0), st = {1}, circuit;
    while (!st.empty()) {
        int u = st.back();
        while (ptr[u] < (int)adj[u].size() && used[adj[u][ptr[u]].second]) ptr[u]++;
        if (ptr[u] == (int)adj[u].size()) { circuit.push_back(u); st.pop_back(); }
        else {
            auto [v, id] = adj[u][ptr[u]];
            used[id] = 1; ptr[u]++; st.push_back(v);
        }
    }
    if ((int)circuit.size() != m + 1) { printf("IMPOSSIBLE\n"); return 0; }  // disconnected
    for (size_t i = 0; i < circuit.size(); i++) printf("%d%c", circuit[i], " \n"[i + 1 == circuit.size()]);
}
