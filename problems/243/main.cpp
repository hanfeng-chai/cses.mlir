#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m; scanf("%d %d", &n, &m);
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<pair<int, int>> E(m);
    for (int i = 0; i < m; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back({b, i}); adj[b].push_back({a, i}); E[i] = {a, b}; }
    vector<int> disc(n + 1, 0), low(n + 1, 0), it(n + 1, 0), pe(n + 1, -1);
    int timer = 0; vector<int> bridges, st;
    for (int s = 1; s <= n; s++) {
        if (disc[s]) continue;
        st.push_back(s); disc[s] = low[s] = ++timer; pe[s] = -1;
        while (!st.empty()) {
            int u = st.back();
            if (it[u] < (int)adj[u].size()) {
                auto [v, eid] = adj[u][it[u]++];
                if (eid == pe[u]) continue;
                if (!disc[v]) { disc[v] = low[v] = ++timer; pe[v] = eid; st.push_back(v); }
                else low[u] = min(low[u], disc[v]);
            } else {
                st.pop_back();
                if (!st.empty()) { int p = st.back(); low[p] = min(low[p], low[u]); if (low[u] > disc[p]) bridges.push_back(pe[u]); }
            }
        }
    }
    printf("%d\n", (int)bridges.size());
    string out;
    for (int eid : bridges) { out += to_string(E[eid].first); out += ' '; out += to_string(E[eid].second); out += '\n'; }
    printf("%s", out.c_str());
}
