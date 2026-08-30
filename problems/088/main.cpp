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
    vector<int> col(n + 1, 0), par(n + 1, 0), it(n + 1, 0);
    vector<int> ans;
    for (int s = 1; s <= n && ans.empty(); s++) {
        if (col[s]) continue;
        vector<int> stk = {s};
        col[s] = 1; par[s] = 0;
        while (!stk.empty() && ans.empty()) {
            int u = stk.back();
            if (it[u] < (int)adj[u].size()) {
                int v = adj[u][it[u]++];
                if (v == par[u]) continue;
                if (col[v] == 1) {  // back edge to an ancestor => cycle
                    ans.push_back(v);
                    for (int x = u; x != v; x = par[x]) ans.push_back(x);
                    ans.push_back(v);
                    break;
                }
                if (col[v] == 0) { col[v] = 1; par[v] = u; stk.push_back(v); }
            } else { col[u] = 2; stk.pop_back(); }
        }
    }
    if (ans.empty()) { printf("IMPOSSIBLE\n"); return 0; }
    printf("%d\n", (int)ans.size());
    for (size_t i = 0; i < ans.size(); i++) printf("%d%c", ans[i], " \n"[i + 1 == ans.size()]);
}
