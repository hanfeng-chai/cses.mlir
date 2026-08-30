#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> adj;
vector<int> bfs(int s) {
    vector<int> d(n + 1, -1);
    queue<int> q; q.push(s); d[s] = 0;
    while (!q.empty()) { int u = q.front(); q.pop(); for (int v : adj[u]) if (d[v] < 0) { d[v] = d[u] + 1; q.push(v); } }
    return d;
}
int main() {
    scanf("%d", &n);
    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); adj[b].push_back(a); }
    // max distance from each node = distance to one of the two diameter endpoints
    auto d1 = bfs(1);
    int u = max_element(d1.begin() + 1, d1.end()) - d1.begin();
    auto du = bfs(u);
    int v = max_element(du.begin() + 1, du.end()) - du.begin();
    auto dv = bfs(v);
    for (int i = 1; i <= n; i++) printf("%d%c", max(du[i], dv[i]), " \n"[i == n]);
}
