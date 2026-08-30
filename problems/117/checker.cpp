#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt(), k = inf.readInt();
    set<pair<int, int>> pairs;
    for (int i = 0; i < k; i++) { int a = inf.readInt(), b = inf.readInt(); pairs.insert({a, b}); }
    long long jr = ans.readLong(), pr = ouf.readLong();
    if (pr != jr) quitf(_wa, "matching size differs: expected %lld, got %lld", jr, pr);
    vector<char> ub(n + 1, 0), ug(m + 1, 0);
    for (long long i = 0; i < pr; i++) {
        int a = ouf.readInt(1, n), b = ouf.readInt(1, m);
        if (!pairs.count({a, b})) quitf(_wa, "pair %d-%d is not a potential pair", a, b);
        if (ub[a]) quitf(_wa, "boy %d appears in two pairs", a);
        if (ug[b]) quitf(_wa, "girl %d appears in two pairs", b);
        ub[a] = ug[b] = 1;
    }
    quitf(_ok, "valid matching of %lld pairs", pr);
}
