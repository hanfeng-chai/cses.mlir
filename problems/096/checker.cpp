#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// SPJ for Round Trip II: a directed cycle of >=2 distinct cities.
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    set<pair<int, int>> es;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(), b = inf.readInt();
        es.insert({a, b});
    }
    string jw = ans.readWord();
    if (jw == "IMPOSSIBLE") {
        string pw = ouf.readWord();
        if (pw != "IMPOSSIBLE") quitf(_wa, "expected IMPOSSIBLE, found %s", pw.c_str());
        quitf(_ok, "IMPOSSIBLE");
    }
    long long pk = ouf.readLong();
    if (pk < 3) quitf(_wa, "directed cycle needs >=2 distinct cities (k>=3), got %lld", pk);
    vector<int> c(pk);
    for (int i = 0; i < pk; i++) c[i] = ouf.readInt(1, n);
    if (c.front() != c.back()) quitf(_wa, "route must start and end at the same city");
    set<int> seen;
    for (int i = 0; i + 1 < (int)c.size(); i++) {
        if (seen.count(c[i])) quitf(_wa, "city %d repeated", c[i]);
        seen.insert(c[i]);
        if (!es.count({c[i], c[i + 1]})) quitf(_wa, "no directed flight %d->%d", c[i], c[i + 1]);
    }
    quitf(_ok, "valid directed cycle of %lld cities", pk);
}
