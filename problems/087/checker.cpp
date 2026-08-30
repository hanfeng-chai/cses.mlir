#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// SPJ for Building Teams: a valid 2-coloring where no edge is monochromatic.
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
    vector<int> col(n + 1);
    col[1] = ouf.readInt(1, 2);
    for (int i = 2; i <= n; i++) col[i] = ouf.readInt(1, 2);
    for (auto [a, b] : edges)
        if (col[a] == col[b]) quitf(_wa, "edge %d-%d is inside one team", a, b);
    quitf(_ok, "valid 2-coloring");
}
