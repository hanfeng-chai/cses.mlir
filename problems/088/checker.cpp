#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// SPJ for Round Trip: a cycle of >=3 distinct cities along existing roads.
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    set<pair<int, int>> es;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(), b = inf.readInt();
        if (a > b) swap(a, b);
        es.insert({a, b});
    }
    string jw = ans.readWord();
    if (jw == "IMPOSSIBLE") {
        string pw = ouf.readWord();
        if (pw != "IMPOSSIBLE") quitf(_wa, "expected IMPOSSIBLE, found %s", pw.c_str());
        quitf(_ok, "IMPOSSIBLE");
    }
    long long pk = ouf.readLong();
    if (pk < 4) quitf(_wa, "round trip needs >=3 distinct cities (k>=4), got %lld", pk);
    vector<int> c(pk);
    for (int i = 0; i < pk; i++) c[i] = ouf.readInt(1, n);
    if (c.front() != c.back()) quitf(_wa, "route must start and end at the same city");
    set<int> seen;
    for (int i = 0; i + 1 < (int)c.size(); i++) {
        if (seen.count(c[i])) quitf(_wa, "city %d repeated", c[i]);
        seen.insert(c[i]);
        int a = c[i], b = c[i + 1];
        if (a > b) swap(a, b);
        if (!es.count({a, b})) quitf(_wa, "no road %d-%d", c[i], c[i + 1]);
    }
    quitf(_ok, "valid round trip of %lld cities", pk);
}
