#include "testlib.h"
using namespace std;

// SPJ for 051 Sum of Four Values
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    long long x = inf.readLong();
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) a[i] = inf.readLong();
    string j = ans.readWord(), p = ouf.readWord();
    bool jI = (j == "IMPOSSIBLE"), pI = (p == "IMPOSSIBLE");
    if (jI) { if (pI) quitf(_ok, "both IMPOSSIBLE"); quitf(_wa, "jury IMPOSSIBLE, participant gave a quad"); }
    if (pI) quitf(_wa, "participant IMPOSSIBLE but a solution exists");
    long long id[4];
    id[0] = atoll(p.c_str());
    for (int t = 1; t < 4; t++) id[t] = ouf.readLong();
    for (int t = 0; t < 4; t++) if (id[t] < 1 || id[t] > n) quitf(_wa, "index out of range");
    for (int s = 0; s < 4; s++) for (int t = s + 1; t < 4; t++) if (id[s] == id[t]) quitf(_wa, "indices must be distinct");
    if (a[id[0]] + a[id[1]] + a[id[2]] + a[id[3]] != x) quitf(_wa, "sum != x");
    quitf(_ok, "valid quad");
}
