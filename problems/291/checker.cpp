#include "testlib.h"
#include <vector>
#include <set>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<int> want(n + 1);
    for (int i = 1; i <= n; i++) want[i] = inf.readInt();
    string jt = ans.readToken();
    bool juryImp = (jt == "IMPOSSIBLE");
    string pt = ouf.readToken();
    if (pt == "IMPOSSIBLE") {
        if (juryImp) quitf(_ok, "IMPOSSIBLE confirmed");
        quitf(_wa, "said IMPOSSIBLE but a solution exists");
    }
    if (juryImp) quitf(_wa, "gave games but it is IMPOSSIBLE");
    int k = atoi(pt.c_str());
    vector<int> got(n + 1, 0);
    set<pair<int, int>> used;
    for (int i = 0; i < k; i++) {
        int a = ouf.readInt(1, n, "a"), b = ouf.readInt(1, n, "b");
        if (a == b) quitf(_wa, "self game %d", a);
        if (a > b) swap(a, b);
        if (used.count({a, b})) quitf(_wa, "duplicate game %d-%d", a, b);
        used.insert({a, b}); got[a]++; got[b]++;
    }
    for (int i = 1; i <= n; i++) if (got[i] != want[i]) quitf(_wa, "player %d plays %d != %d", i, got[i], want[i]);
    quitf(_ok, "%d games", k);
}
