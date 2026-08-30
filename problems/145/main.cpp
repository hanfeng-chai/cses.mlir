#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    scanf("%d", &n);
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) { int a, b; scanf("%d %d", &a, &b); adj[a].push_back(b); adj[b].push_back(a); }
    vector<int> par(n + 1, 0), order; order.reserve(n);
    vector<char> vis(n + 1, 0);
    vector<int> st = {1}; vis[1] = 1; par[1] = 0;
    while (!st.empty()) { int u = st.back(); st.pop_back(); order.push_back(u); for (int v : adj[u]) if (!vis[v]) { vis[v] = 1; par[v] = u; st.push_back(v); } }
    // d0[u]=best matching with u unmatched, d1[u]=u matched to a child
    vector<long long> d0(n + 1, 0), d1(n + 1, 0);
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        long long sum = 0, best = 0;
        for (int v : adj[u]) if (v != par[u]) sum += max(d0[v], d1[v]);
        for (int v : adj[u]) if (v != par[u]) best = max(best, 1 + d0[v] - max(d0[v], d1[v]));
        d0[u] = sum; d1[u] = sum + best;
    }
    printf("%lld\n", max(d0[1], d1[1]));
}
