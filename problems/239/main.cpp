#include <bits/stdc++.h>
using namespace std;
const int N = 50000;
int n, m, q;
vector<int> adj[N + 1];
int low[N + 1], num[N + 1], comp[N + 1], timer_ = 0, nc = 0;
bool onstk[N + 1];
int stk[N + 1], sp = 0;
bitset<N> reach[N + 1];
int main() {
    scanf("%d %d %d", &n, &m, &q);
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); edges[i] = {a, b}; }
    // iterative Tarjan SCC
    vector<int> idx(n + 1, 0);
    vector<int> callStack, ci;
    for (int s = 1; s <= n; s++) {
        if (num[s]) continue;
        callStack.push_back(s); ci.push_back(0);
        while (!callStack.empty()) {
            int u = callStack.back();
            if (ci.back() == 0) { num[u] = low[u] = ++timer_; stk[sp++] = u; onstk[u] = true; }
            if (ci.back() < (int)adj[u].size()) {
                int v = adj[u][ci.back()++];
                if (!num[v]) { callStack.push_back(v); ci.push_back(0); }
                else if (onstk[v]) low[u] = min(low[u], num[v]);
            } else {
                if (low[u] == num[u]) {
                    nc++;
                    while (true) { int w = stk[--sp]; onstk[w] = false; comp[w] = nc; if (w == u) break; }
                }
                callStack.pop_back(); ci.pop_back();
                if (!callStack.empty()) { int p = callStack.back(); low[p] = min(low[p], low[u]); }
            }
        }
    }
    // condensed DAG (comp ids 1..nc); reverse topo via comp order: Tarjan gives reverse topo (comp assigned in reverse topo order)
    // build DAG adjacency
    vector<vector<int>> dag(nc + 1);
    vector<int> indeg(nc + 1, 0);
    for (auto &e : edges) { int ca = comp[e.first], cb = comp[e.second]; if (ca != cb) { dag[ca].push_back(cb); indeg[cb]++; } }
    vector<int> topo; queue<int> Q;
    for (int i = 1; i <= nc; i++) if (!indeg[i]) Q.push(i);
    while (!Q.empty()) { int u = Q.front(); Q.pop(); topo.push_back(u); for (int v : dag[u]) if (--indeg[v] == 0) Q.push(v); }
    for (int i = (int)topo.size() - 1; i >= 0; i--) { int u = topo[i]; reach[u][u - 1] = 1; for (int v : dag[u]) reach[u] |= reach[v]; }
    string out;
    while (q--) { int a, b; scanf("%d %d", &a, &b); out += (reach[comp[a]][comp[b] - 1] ? "YES\n" : "NO\n"); }
    cout << out;
}
