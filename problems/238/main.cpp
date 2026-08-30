#include <bits/stdc++.h>
using namespace std;
const int N = 50000;
bitset<N> reach[N + 1];
int main() {
    int n, m; scanf("%d %d", &n, &m);
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); indeg[b]++; }
    vector<int> topo; queue<int> q;
    for (int i = 1; i <= n; i++) if (!indeg[i]) q.push(i);
    while (!q.empty()) { int u = q.front(); q.pop(); topo.push_back(u); for (int v : adj[u]) if (--indeg[v] == 0) q.push(v); }
    for (int i = (int)topo.size() - 1; i >= 0; i--) {
        int u = topo[i]; reach[u][u - 1] = 1;
        for (int v : adj[u]) reach[u] |= reach[v];
    }
    string out;
    for (int i = 1; i <= n; i++) { out += to_string((int)reach[i].count()); out += " \n"[i == n]; }
    cout << out;
}
