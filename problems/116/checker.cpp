#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    set<pair<int, int>> es;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(), b = inf.readInt();
        es.insert({min(a, b), max(a, b)});
        adj[a].push_back(b); adj[b].push_back(a);
    }
    long long jk = ans.readLong(), pk = ouf.readLong();
    if (pk != jk) quitf(_wa, "cut size differs: expected %lld, got %lld", jk, pk);
    set<pair<int, int>> removed;
    for (long long i = 0; i < pk; i++) {
        int a = ouf.readInt(1, n), b = ouf.readInt(1, n);
        auto key = make_pair(min(a, b), max(a, b));
        if (!es.count(key)) quitf(_wa, "street %d-%d does not exist", a, b);
        removed.insert(key);
    }
    vector<char> vis(n + 1, 0);
    queue<int> q; q.push(1); vis[1] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (removed.count({min(u, v), max(u, v)})) continue;
            if (!vis[v]) { vis[v] = 1; q.push(v); }
        }
    }
    if (vis[n]) quitf(_wa, "harbor still reachable after closing the streets");
    quitf(_ok, "valid minimum cut of %lld streets", pk);
}
