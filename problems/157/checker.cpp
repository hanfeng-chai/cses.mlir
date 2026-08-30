#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// SPJ for Finding a Centroid: the output node must make every component <= n/2.
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) { int a = inf.readInt(), b = inf.readInt(); adj[a].push_back(b); adj[b].push_back(a); }
    int c = ouf.readInt(1, n);
    // root at c, compute subtree sizes iteratively; check max component <= n/2
    vector<int> par(n + 1, 0), order, sz(n + 1, 1);
    vector<char> vis(n + 1, 0); vis[c] = 1;
    vector<int> st = {c};
    while (!st.empty()) { int u = st.back(); st.pop_back(); order.push_back(u); for (int v : adj[u]) if (!vis[v]) { vis[v] = 1; par[v] = u; st.push_back(v); } }
    for (int i = (int)order.size() - 1; i >= 0; i--) { int u = order[i]; if (u != c) sz[par[u]] += sz[u]; }
    int maxpart = 0;
    for (int v : adj[c]) maxpart = max(maxpart, sz[v]);  // each neighbour heads one component
    if (maxpart > n / 2) quitf(_wa, "node %d is not a centroid: a component has %d > %d nodes", c, maxpart, n / 2);
    quitf(_ok, "valid centroid %d", c);
}
