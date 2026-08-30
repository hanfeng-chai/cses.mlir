#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// SPJ for Course Schedule: a valid topological order (or IMPOSSIBLE).
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) { int a = inf.readInt(), b = inf.readInt(); edges[i] = {a, b}; }
    string jw = ans.readWord();
    if (jw == "IMPOSSIBLE") {
        string pw = ouf.readWord();
        if (pw != "IMPOSSIBLE") quitf(_wa, "expected IMPOSSIBLE, found %s", pw.c_str());
        quitf(_ok, "IMPOSSIBLE");
    }
    vector<int> pos(n + 1, 0), seen(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int x = ouf.readInt(1, n);
        if (seen[x]) quitf(_wa, "course %d repeated", x);
        seen[x] = 1; pos[x] = i;
    }
    for (auto [a, b] : edges)
        if (pos[a] >= pos[b]) quitf(_wa, "course %d not before %d", a, b);
    quitf(_ok, "valid topological order");
}
