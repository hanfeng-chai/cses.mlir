#include "testlib.h"
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    string jt = ans.readToken();
    bool juryImp = (jt == "IMPOSSIBLE");
    string pt = ouf.readToken();
    if (pt == "IMPOSSIBLE") {
        if (juryImp) quitf(_ok, "IMPOSSIBLE confirmed");
        quitf(_wa, "said IMPOSSIBLE but solution exists");
    }
    if (juryImp) quitf(_wa, "gave grid but IMPOSSIBLE");
    vector<vector<int>> g(n, vector<int>(n));
    vector<int> cnt(n + 1, 0);
    g[0][0] = atoi(pt.c_str());
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        if (i == 0 && j == 0) {} else g[i][j] = ouf.readInt(1, n, "cell");
        if (g[i][j] < 1 || g[i][j] > n) quitf(_wa, "cell out of range");
        cnt[g[i][j]]++;
    }
    for (int v = 1; v <= n; v++) if (cnt[v] != n) quitf(_wa, "value %d appears %d times, not %d", v, cnt[v], n);
    set<ll> sums;
    for (int i = 0; i < n; i++) { ll s = 0; for (int j = 0; j < n; j++) s += g[i][j]; if (!sums.insert(s).second) quitf(_wa, "duplicate sum %lld", s); }
    for (int j = 0; j < n; j++) { ll s = 0; for (int i = 0; i < n; i++) s += g[i][j]; if (!sums.insert(s).second) quitf(_wa, "duplicate sum %lld", s); }
    quitf(_ok, "valid grid, %d distinct sums", (int)sums.size());
}
