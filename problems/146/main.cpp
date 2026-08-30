#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> adj;
pair<int, int> bfs(int s) {  // returns (farthest node, its distance)
    vector<int> d(n + 1, -1);
    queue<int> q; q.push(s); d[s] = 0; int far = s;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (d[u] > d[far]) far = u;
        for (int v : adj[u]) if (d[v] < 0) { d[v] = d[u] + 1; q.push(v); }
    }
    return {far, d[far]};
}
int main() {
    scanf("%d", &n);
    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); adj[b].push_back(a); }
    int u = bfs(1).first;
    printf("%d\n", bfs(u).second);
}
