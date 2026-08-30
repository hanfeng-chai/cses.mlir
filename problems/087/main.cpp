#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b); adj[b].push_back(a);
    }
    vector<int> col(n + 1, 0);
    bool ok = true;
    for (int s = 1; s <= n && ok; s++)
        if (!col[s]) {
            col[s] = 1;
            queue<int> q; q.push(s);
            while (!q.empty() && ok) {
                int u = q.front(); q.pop();
                for (int v : adj[u]) {
                    if (!col[v]) { col[v] = 3 - col[u]; q.push(v); }
                    else if (col[v] == col[u]) { ok = false; break; }
                }
            }
        }
    if (!ok) { printf("IMPOSSIBLE\n"); return 0; }
    for (int i = 1; i <= n; i++) printf("%d%c", col[i], " \n"[i == n]);
}
