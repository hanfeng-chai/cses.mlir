#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b); outdeg[a]++; indeg[b]++;
    }
    // directed Euler path 1->n: out[1]-in[1]=1, in[n]-out[n]=1, others balanced
    bool ok = (outdeg[1] - indeg[1] == 1) && (indeg[n] - outdeg[n] == 1);
    for (int i = 1; i <= n && ok; i++)
        if (i != 1 && i != n && indeg[i] != outdeg[i]) ok = false;
    if (!ok) { printf("IMPOSSIBLE\n"); return 0; }
    vector<int> ptr(n + 1, 0), st = {1}, path;
    while (!st.empty()) {
        int u = st.back();
        if (ptr[u] < (int)adj[u].size()) st.push_back(adj[u][ptr[u]++]);
        else { path.push_back(u); st.pop_back(); }
    }
    reverse(path.begin(), path.end());
    if ((int)path.size() != m + 1 || path.front() != 1 || path.back() != n) {
        printf("IMPOSSIBLE\n"); return 0;  // disconnected
    }
    for (size_t i = 0; i < path.size(); i++) printf("%d%c", path[i], " \n"[i + 1 == path.size()]);
}
