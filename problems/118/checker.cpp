#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    set<pair<int, int>> es;
    for (int i = 0; i < m; i++) { int a = inf.readInt(), b = inf.readInt(); es.insert({a, b}); }
    long long jk = ans.readLong(), pk = ouf.readLong();
    if (pk != jk) quitf(_wa, "route count differs: expected %lld, got %lld", jk, pk);
    set<pair<int, int>> usedEdges;
    for (long long p = 0; p < pk; p++) {
        long long len = ouf.readLong();
        if (len < 2) quitf(_wa, "route too short");
        vector<int> path(len);
        for (int i = 0; i < len; i++) path[i] = ouf.readInt(1, n);
        if (path.front() != 1) quitf(_wa, "route must start at room 1");
        if (path.back() != n) quitf(_wa, "route must end at room n");
        for (int i = 0; i + 1 < (int)len; i++) {
            auto key = make_pair(path[i], path[i + 1]);
            if (!es.count(key)) quitf(_wa, "teleporter %d->%d does not exist", path[i], path[i + 1]);
            if (usedEdges.count(key)) quitf(_wa, "teleporter %d->%d used twice", path[i], path[i + 1]);
            usedEdges.insert(key);
        }
    }
    quitf(_ok, "valid %lld edge-disjoint routes", pk);
}
