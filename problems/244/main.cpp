#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m; scanf("%d %d", &n, &m);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); adj[b].push_back(a); }
    vector<int> disc(n + 1, 0), low(n + 1, 0), it(n + 1, 0), par(n + 1, 0);
    int timer = 0; vector<bool> isArt(n + 1, false); vector<int> st;
    for (int s = 1; s <= n; s++) {
        if (disc[s]) continue;
        int rootChildren = 0;
        st.push_back(s); disc[s] = low[s] = ++timer; par[s] = 0;
        while (!st.empty()) {
            int u = st.back();
            if (it[u] < (int)adj[u].size()) {
                int v = adj[u][it[u]++];
                if (v == par[u]) continue;
                if (!disc[v]) { disc[v] = low[v] = ++timer; par[v] = u; st.push_back(v); if (u == s) rootChildren++; }
                else low[u] = min(low[u], disc[v]);
            } else {
                st.pop_back();
                if (!st.empty()) { int p = st.back(); low[p] = min(low[p], low[u]); if (p != s && low[u] >= disc[p]) isArt[p] = true; }
            }
        }
        if (rootChildren > 1) isArt[s] = true;
    }
    vector<int> res;
    for (int i = 1; i <= n; i++) if (isArt[i]) res.push_back(i);
    printf("%d\n", (int)res.size());
    string out;
    for (int x : res) { out += to_string(x); out += '\n'; }
    printf("%s", out.c_str());
}
