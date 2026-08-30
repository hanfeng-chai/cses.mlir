#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<vector<int>> adj(n + 1), radj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b); radj[b].push_back(a);
    }
    // Kosaraju SCC: 1st pass finish order
    vector<int> order; order.reserve(n);
    vector<char> vis(n + 1, 0);
    vector<int> idx(n + 1, 0);
    for (int s = 1; s <= n; s++)
        if (!vis[s]) {
            vector<int> st = {s}; vis[s] = 1;
            while (!st.empty()) {
                int u = st.back();
                if (idx[u] < (int)adj[u].size()) {
                    int v = adj[u][idx[u]++];
                    if (!vis[v]) { vis[v] = 1; st.push_back(v); }
                } else { order.push_back(u); st.pop_back(); }
            }
        }
    // 2nd pass on reverse graph in reverse finish order
    vector<int> comp(n + 1, -1);
    int k = 0;
    for (int i = n - 1; i >= 0; i--) {
        int s = order[i];
        if (comp[s] == -1) {
            vector<int> st = {s}; comp[s] = k;
            while (!st.empty()) {
                int u = st.back(); st.pop_back();
                for (int v : radj[u]) if (comp[v] == -1) { comp[v] = k; st.push_back(v); }
            }
            k++;
        }
    }
    printf("%d\n", k);
    for (int i = 1; i <= n; i++) printf("%d%c", comp[i] + 1, " \n"[i == n]);
}
