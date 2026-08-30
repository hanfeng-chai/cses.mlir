#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// SPJ for Flight Routes Check: YES if strongly connected, else a pair a,b with no a->b path.
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) { int a = inf.readInt(), b = inf.readInt(); adj[a].push_back(b); }
    string jw = ans.readWord(), pw = ouf.readWord();
    if (jw == "YES") {
        if (pw != "YES") quitf(_wa, "expected YES, found %s", pw.c_str());
        quitf(_ok, "YES");
    }
    if (pw != "NO") quitf(_wa, "expected NO, found %s", pw.c_str());
    int a = ouf.readInt(1, n), b = ouf.readInt(1, n);
    // verify b is NOT reachable from a
    vector<char> vis(n + 1, 0);
    queue<int> q; q.push(a); vis[a] = 1;
    while (!q.empty()) { int u = q.front(); q.pop(); for (int v : adj[u]) if (!vis[v]) { vis[v] = 1; q.push(v); } }
    if (vis[b]) quitf(_wa, "city %d IS reachable from %d", b, a);
    quitf(_ok, "correct: no route %d -> %d", a, b);
}
