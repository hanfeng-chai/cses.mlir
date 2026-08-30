#include "testlib.h"
#include <vector>
#include <set>
#include <map>
using namespace std;
typedef long long ll;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt(), k = inf.readInt();
    set<pair<int, int>> edges;
    for (int i = 0; i < m; i++) { int a = inf.readInt(), b = inf.readInt(); edges.insert({a, b}); }
    string jt = ans.readToken();
    bool juryNo = (jt == "-1");
    string pt = ouf.readToken();
    if (pt == "-1") { if (juryNo) quitf(_ok, "no solution"); quitf(_wa, "participant says -1 but a solution exists"); }
    ll pcost = atoll(pt.c_str());
    ll jcost = juryNo ? -1 : atoll(jt.c_str());
    if (pcost != jcost) quitf(_wa, "coins %lld != optimal %lld", pcost, jcost);
    set<pair<int, int>> usedEdges;
    ll total = 0;
    for (int r = 0; r < k; r++) {
        int len = ouf.readInt(2, n, "route length");
        vector<int> path(len);
        for (int i = 0; i < len; i++) path[i] = ouf.readInt(1, n, "room");
        if (path[0] != 1) quitf(_wa, "route %d does not start at room 1", r + 1);
        if (path[len - 1] != n) quitf(_wa, "route %d does not end at room %d", r + 1, n);
        for (int i = 0; i + 1 < len; i++) {
            pair<int, int> e = {path[i], path[i + 1]};
            if (!edges.count(e)) quitf(_wa, "route %d uses nonexistent teleporter %d->%d", r + 1, e.first, e.second);
            if (usedEdges.count(e)) quitf(_wa, "teleporter %d->%d used more than once", e.first, e.second);
            usedEdges.insert(e); total++;
        }
    }
    if (total != pcost) quitf(_wa, "total coins %lld != stated %lld", total, pcost);
    quitf(_ok, "%d routes, %lld coins", k, pcost);
}
