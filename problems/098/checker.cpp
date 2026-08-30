#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
// SPJ for Longest Flight Route: a longest 1..n path in a DAG.
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    set<pair<int, int>> es;
    for (int i = 0; i < m; i++) { int a = inf.readInt(), b = inf.readInt(); es.insert({a, b}); }
    string jw = ans.readWord();
    if (jw == "IMPOSSIBLE") {
        string pw = ouf.readWord();
        if (pw != "IMPOSSIBLE") quitf(_wa, "expected IMPOSSIBLE, found %s", pw.c_str());
        quitf(_ok, "IMPOSSIBLE");
    }
    long long jk = atoll(jw.c_str());
    long long pk = ouf.readLong();
    if (pk != jk) quitf(_wa, "city count differs: expected %lld, found %lld", jk, pk);
    vector<int> path(pk);
    for (int i = 0; i < pk; i++) path[i] = ouf.readInt(1, n);
    if (path.front() != 1) quitf(_wa, "route must start at 1");
    if (path.back() != n) quitf(_wa, "route must end at n");
    for (int i = 0; i + 1 < (int)path.size(); i++)
        if (!es.count({path[i], path[i + 1]})) quitf(_wa, "no flight %d->%d", path[i], path[i + 1]);
    quitf(_ok, "longest route of %lld cities", pk);
}
