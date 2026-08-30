#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
vector<int> par;
int find(int x) { return par[x] == x ? x : par[x] = find(par[x]); }
// SPJ for Building Roads: the k added roads must connect everything, k minimal.
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    par.resize(n + 1);
    for (int i = 1; i <= n; i++) par[i] = i;
    for (int i = 0; i < m; i++) { int a = inf.readInt(), b = inf.readInt(); par[find(a)] = find(b); }
    long long jk = ans.readLong(), pk = ouf.readLong();
    if (pk != jk) quitf(_wa, "k differs: expected %lld, found %lld", jk, pk);
    for (long long i = 0; i < pk; i++) {
        int a = ouf.readInt(1, n), b = ouf.readInt(1, n);
        par[find(a)] = find(b);
    }
    int comp = 0;
    for (int i = 1; i <= n; i++) if (find(i) == i) comp++;
    if (comp != 1) quitf(_wa, "after adding roads %d components remain", comp);
    quitf(_ok, "connected with %lld roads", pk);
}
