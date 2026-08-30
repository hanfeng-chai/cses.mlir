#include "testlib.h"
using namespace std;

// SPJ for 050 Sum of Three Values
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    long long x = inf.readLong();
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) a[i] = inf.readLong();
    string j = ans.readWord(), p = ouf.readWord();
    bool jI = (j == "IMPOSSIBLE"), pI = (p == "IMPOSSIBLE");
    if (jI) { if (pI) quitf(_ok, "both IMPOSSIBLE"); quitf(_wa, "jury IMPOSSIBLE, participant gave a triple"); }
    if (pI) quitf(_wa, "participant IMPOSSIBLE but a solution exists");
    long long i1 = atoll(p.c_str()), i2 = ouf.readLong(), i3 = ouf.readLong();
    if (i1 < 1 || i1 > n || i2 < 1 || i2 > n || i3 < 1 || i3 > n) quitf(_wa, "index out of range");
    if (i1 == i2 || i1 == i3 || i2 == i3) quitf(_wa, "indices must be distinct");
    if (a[i1] + a[i2] + a[i3] != x) quitf(_wa, "sum %lld != %lld", a[i1] + a[i2] + a[i3], x);
    quitf(_ok, "valid triple");
}
